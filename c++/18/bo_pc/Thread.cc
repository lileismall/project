
#include "Thread.h"

namespace ll
{

Thread::Thread(funccallback &&func)
    : _pthid(0)
    , _isRunning(false) 
    , _func(move(func))
    {}

Thread::~Thread()
{}

void Thread::star()
{
    pthread_create(&_pthid,nullptr,threadfunc,this);
    _isRunning = true;
}

void Thread::join()
{
    if(_isRunning)
    {
        pthread_join(_pthid,NULL);
    }
}

void *Thread::threadfunc(void *arg)
{
    Thread *pthread = static_cast<Thread*>(arg);
    if(pthread)
    {
        pthread->_func();
    }
    return 0;
}

}
