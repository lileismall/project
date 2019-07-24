#pragma once

#include "MutexLock.h"
#include "Condition.h"
#include "Task.h"

#include <vector>
#include <queue>

using namespace std;

namespace ll
{

class TaskQueue
{
    using ElemType = Task*;
public:
    TaskQueue(size_t queSize = 10);
    ~TaskQueue();

    void push(ElemType);
    ElemType pop();
    bool empty();
    bool full();
    void wakeup();
private:
    size_t _queSize;
    queue<ElemType> _que;
    MutexLock _mutex;
    Condition _notFull;
    Condition _notEmpty;
    bool _flag;
};

}
