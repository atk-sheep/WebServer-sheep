#include "threadPool.hpp"

threadPool threadPool::globalThreadPool{};

threadPool::threadPool(uint8_t threadNum, uint8_t queueSize)
: m_threadNum(threadNum), m_queueSize(queueSize)
{

}

threadPool& threadPool::instance(){
    return globalThreadPool;
}

