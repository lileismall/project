
#include "Thread.h"

namespace ll
{

Thread::Thread()
    : _pthid(0)
    , _isRunning(false) 
    {}

Thread::~Thread()
{
    if(_isRunning)
        pthread_detach(_pthid);
}

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
        _isRunning = false;
    }
}

void *Thread::threadfunc(void *arg)
{
    Thread *pthread = static_cast<Thread*>(arg);
    if(pthread)
    {
        pthread->run();
    }
    return 0;
}

}