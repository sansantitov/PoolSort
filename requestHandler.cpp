#include "requestHandler.h"
#include "poolThread.h"


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


