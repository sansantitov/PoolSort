#pragma once
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <thread>
#include <functional>

class PoolThread {
public:
    PoolThread() = default;
    void start();
    void stop();
    template<typename F, typename... Args>
    void push_task(F&& f, Args&&... args);
    void threadFunc();

private:
    std::vector<std::thread> m_threads;
    std::queue<std::function<void()>> m_task_queue;
    std::mutex m_locker;
    std::condition_variable m_event_holder;
    volatile bool m_work;
};



void PoolThread::start() {
    m_work = true;
    for (int i = 0; i < 4; i++) {
        m_threads.push_back(std::thread(&PoolThread::threadFunc, this));
    }
}

void PoolThread::stop() {
    m_work = false;
    m_event_holder.notify_all();
    for (auto& t : m_threads) t.join();
}



void PoolThread::threadFunc() {
    while (true) {
        std::function<void()> task_to_do;
        {
            std::unique_lock<std::mutex> l(m_locker);
            if (m_task_queue.empty() && !m_work)
                return;
            if (m_task_queue.empty()) {
                m_event_holder.wait(l, [&]() {return !m_task_queue.empty() || !m_work; });
            }
            if (!m_task_queue.empty()) {
                task_to_do = m_task_queue.front();
                m_task_queue.pop();
            }
        }
        if (task_to_do) task_to_do();
    }
}

template<typename F, typename... Args>
void PoolThread::push_task(F&& f, Args&&... args) {
    {
        std::lock_guard<std::mutex> l(m_locker);
        m_task_queue.push(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    }
    m_event_holder.notify_one();
}


