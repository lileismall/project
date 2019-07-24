#pragma once
#include "NonCopy.h"

#include <pthread.h>
#include <functional>

namespace ll
{

class Thread
{
    using funccallback = std::function<void()>;
public:
    Thread(funccallback &&func);
    ~Thread();

    void star();
    void join();

private:
    static void *threadfunc(void *); //这里要用static是为了去除自带的this参数

private:
    pthread_t _pthid;
    bool _isRunning;
    funccallback _func;

};

}
