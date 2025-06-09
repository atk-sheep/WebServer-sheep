#ifndef THREADPOLL_HPP_
#define THREADPOLL_HPP_

#include <thread>
#include <mutex>
#include <condition_variable>
#include "utils.hpp"

// Eager Singleton
class threadPool
{
private:
    std::mutex tp_lock{};
    std::condition_variable tp_condVar{};
    static threadPool globalThreadPool;

    uint8_t m_threadNum{THREADNUM};
    uint8_t m_queueSize{QUEUESIZE};

private:
    explicit threadPool()=default;
    explicit threadPool(uint8_t threadNum, uint8_t queueSize);
    ~threadPool()=default;

public:
    static threadPool& instance();
    bool threadCreate();
    bool threadAdd();
};

inline threadPool& getThreadPool() {return threadPool::instance();}

#endif