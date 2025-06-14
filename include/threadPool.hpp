#ifndef THREADPOLL_HPP_
#define THREADPOLL_HPP_

#include <thread>
#include <mutex>
#include <condition_variable>
#include "utils.hpp"
#include "reQuestData.hpp"
#include <functional>
#include <vector>
#include <list>
#include <iostream>

struct threadPoolTask
{
    std::function<void(std::shared_ptr<baseData>)> func;
    std::shared_ptr<baseData> data;

    threadPoolTask() = default;
    threadPoolTask(std::shared_ptr<baseData> pdata, std::function<void(std::shared_ptr<baseData>)> fun)
        : data(pdata), func(fun){

        }
    
    threadPoolTask(threadPoolTask const&) = default;
    threadPoolTask(threadPoolTask&&) = default;
    threadPoolTask& operator=(threadPoolTask const&) = default;
    threadPoolTask& operator=(threadPoolTask &&) = default;

};


// Eager Singleton
class threadPool
{
private:
    std::mutex m_taskLock{};
    std::condition_variable m_taskCondVar{};
    static threadPool globalThreadPool;

    uint8_t m_threadNum{THREADNUM};
    uint8_t m_queueSize{QUEUESIZE};

    std::vector<std::thread> m_threads{};
    std::list<threadPoolTask> m_taskList{};

    bool m_start{false};

private:
    explicit threadPool();
    explicit threadPool(uint8_t threadNum, uint8_t queueSize);
    ~threadPool();

    threadPool(const threadPool &) = delete;
    threadPool(threadPool &&) = delete;
    threadPool& operator=(const threadPool &) = delete;
    threadPool& operator=(threadPool &&) = delete;

    void threadHandler();

    void deinit();

public:
    static threadPool& instance();
    bool threadCreate();
    bool threadAdd(std::shared_ptr<baseData> req, std::function<void(std::shared_ptr<baseData>)> func);
};

// inline, allow redefinition then merge to one instance when link; no inline, multiple definition
inline threadPool& getThreadPool() {return threadPool::instance();}

#endif