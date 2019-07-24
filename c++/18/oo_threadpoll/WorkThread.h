#pragma once
#include "Thread.h"
#include "Threadpoll.h"


namespace ll
{

class WorkThread
:public Thread
{
public:
    WorkThread(Threadpoll &threadpoll) 
    : _threadpoll(threadpoll)
    {}

    ~WorkThread() 
    {
        cout << "~WorkThread()" << endl;
    }

    void run()
    {
        _threadpoll.threadfunc();
    }
private:
    Threadpoll &_threadpoll;
};

}
