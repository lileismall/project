#pragma once
#include "NonCopy.h"

#include <pthread.h>
#include <functional>

using namespace std;

namespace ll
{

class Thread
{
public:
    using funccallback = function<void()>;

    Thread(funccallback && func);
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
