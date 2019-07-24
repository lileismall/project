
#include "TaskQueue.h"

using namespace std;

namespace ll
{


TaskQueue::TaskQueue(size_t queSize)
: _queSize(queSize)
, _mutex()
, _notFull(_mutex)
, _notEmpty(_mutex)
{
}

TaskQueue::~TaskQueue()
{
       
}

void TaskQueue::push(ElemType elem)
{
    MutexLockGuard autolock(_mutex);
    while(full())
    {
        _notFull.wait();
    }
    _que.push(elem);
    _notEmpty.notify();
}

TaskQueue::ElemType TaskQueue::pop()
{
    MutexLockGuard autolock(_mutex); //RAII技术
    while(empty())
    {
        _notEmpty.wait();
    }
    ElemType elem = _que.front();
    _que.pop();
    _notFull.notify();
    return elem;
}

bool TaskQueue::full()
{
    return _que.size() == _queSize;
}

bool TaskQueue::empty()
{
    return 0 == _que.size();
}

}
