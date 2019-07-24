
#include "TaskQueue.h"

using namespace std;

namespace ll
{


TaskQueue::TaskQueue(size_t queSize)
: _queSize(queSize)
, _mutex()
, _notFull(_mutex)
, _notEmpty(_mutex)
, _flag(true)
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
    while(_flag && empty()) //重点
    {
        _notEmpty.wait();
    }
    if(_flag)
    {
        ElemType elem = _que.front();
        _que.pop();
        _notFull.notify();
        return elem;
    }else{
        return 0;
    }
}

bool TaskQueue::full()
{
    return _que.size() == _queSize;
}

bool TaskQueue::empty()
{
    return 0 == _que.size();
}

void TaskQueue::wakeup()
{
    _flag = false;
    _notEmpty.notifyAll();
}

}
