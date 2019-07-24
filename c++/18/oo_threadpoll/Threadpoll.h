#pragma once
#include "TaskQueue.h"
#include "Thread.h"

#include <vector>
#include <memory>

using namespace std;

namespace ll
{

/* class Task; */
class Threadpoll
{
    friend class WorkThread;
public:
    Threadpoll(size_t threadNum = 4,size_t queSize = 5);
    ~Threadpoll() {if(!_isExit) stop();}

    void start();
    void stop();
    void addTask(Task *task);
    Task *getTask();

private:
    void threadfunc();

private:
    size_t _threadNum;
    size_t _queSize;
    vector<unique_ptr<Thread>> _threads;
    TaskQueue _taskQue;
    bool _isExit;
};

}
