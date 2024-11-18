#pragma once
#include "poolThread.h"


class RequestHandler {
public:
    RequestHandler();
    ~RequestHandler();
    template<typename F, typename... Args>
    void push_task(F&& f, Args&&... args);

private:
    PoolThread m_pool;

};


RequestHandler::RequestHandler() {
    m_pool.start();
}

RequestHandler::~RequestHandler() {
    m_pool.stop();
}

template<typename F, typename... Args>
void RequestHandler::push_task(F&& f, Args&&... args) {
    m_pool.push_task(std::forward<F>(f), std::forward<Args>(args)...);
}



