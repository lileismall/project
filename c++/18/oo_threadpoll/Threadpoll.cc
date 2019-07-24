
#include "Threadpoll.h"
#include "WorkThread.h"
#include "Task.h"
#include <unistd.h>

namespace ll
{

Threadpoll::Threadpoll(size_t threadNum,size_t queSize)
    : _threadNum(threadNum)
    , _queSize(queSize)
    , _isExit(false)
    {
        _threads.reserve(4);
    }

void Threadpoll::start()
{
    for(size_t i=0;i<_threadNum;i++)
    {
        unique_ptr<Thread> thread(new WorkThread(*this));
        _threads.push_back(move(thread));
    }
    for(auto &thread: _threads)
    {
        thread->star();
    }
}

void Threadpoll::stop()
{
    if(!_isExit)
    {
        while(!_taskQue.empty()) //如果不空在这里循环,让子线程任务执行完
        {
            sleep(1);
        }
        _isExit = true;
        _taskQue.wakeup();
        for(auto &thread : _threads)
        {
            thread->join();
        }
    }
}

void Threadpoll::addTask(Task *task)
{
    _taskQue.push(task);
}

Task* Threadpoll::getTask()
{
    return _taskQue.pop();
}

void Threadpoll::threadfunc()
{
    while(!_isExit)
    {
        Task *task = getTask();
        if(task)
        {
            task->process();
        }
    }
}

}
