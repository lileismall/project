#pragma once

#include "MutexLock.h"
#include "Condition.h"

#include <vector>
#include <queue>

using namespace std;

namespace ll
{

class TaskQueue
{
    using ElemType = int;
public:
    TaskQueue(size_t queSize = 10);
    ~TaskQueue();

    void push(ElemType);
    ElemType pop();
    bool empty();
    bool full();
private:
    size_t _queSize;
    queue<ElemType> _que;
    MutexLock _mutex;
    Condition _notFull;
    Condition _notEmpty;
};

}
