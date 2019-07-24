#pragma once
#include "NonCopy.h"

#include <pthread.h>

namespace ll
{

class Thread
{
public:
    Thread();
    ~Thread();

    void star();
    void join();

private:
    virtual void run() = 0;
    static void *threadfunc(void *); //这里要用static是为了去除自带的this参数

private:
    pthread_t _pthid;
    bool _isRunning;

};

}
