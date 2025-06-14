#include "threadPool.hpp"
#include <chrono>

threadPool threadPool::globalThreadPool{};

threadPool::threadPool()
{
    m_start = true;
}

threadPool::threadPool(uint8_t threadNum, uint8_t queueSize)
: m_threadNum(threadNum), m_queueSize(queueSize)
{
    m_start = true;
}

threadPool& threadPool::instance(){
    return globalThreadPool;
}

threadPool::~threadPool(){
    m_start = false;

    // thread join
    for(auto & t: m_threads) {
        if(t.joinable()) {
            t.join();
        }
    }

    // release all task
    // intelligent pointer, do nothing
}

bool threadPool::threadCreate(){
    bool ret = false;

    m_threads.reserve(m_threadNum);

    for(uint8_t i=0; i<m_threadNum; ++i) {
        std::thread t_thread(std::bind(&threadPool::threadHandler, this));

        if(!t_thread.joinable()){
            std::cout<< "thread create failed!" <<std::endl;
            return false;
        }

        m_threads.emplace_back(std::move(t_thread));
    }


    
}

void threadPool::threadHandler(){
    std::chrono::seconds timeout = std::chrono::seconds(2);

    threadPoolTask task{};

    while (true)
    {
        if(!m_start) break;

        {
            std::unique_lock<std::mutex> lk(m_taskLock);    // lock default
            // cant use wait_for, avoid to continue carry out if condtion is false when timeout
            m_taskCondVar.wait(lk, [this](){return !m_taskList.empty();});

            threadPoolTask task = std::move(m_taskList.front());

            m_taskList.pop_front();
        }

        (task.func)(task.data);
    }
    
}

void threadPool::deinit(){

}

bool threadPool::threadAdd(std::shared_ptr<baseData> req, std::function<void(std::shared_ptr<baseData>)> func) {
    {
        std::unique_lock<std::mutex> lk(m_taskLock);

        m_taskList.emplace_back(req, func);
    }

    
}
