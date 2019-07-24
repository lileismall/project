#pragma once
#include "Thread.h"

namespace ll
{
class TaskQueue;

class Producer
:public Thread
{
public:
    Producer(TaskQueue &taskQueue); 
    ~Producer();

private:
    void run();
private:
    TaskQueue &_taskQue;
};

class Consumer
:public Thread
{
public:
    Consumer(TaskQueue &taskQue);
    ~Consumer(){}

private:
    void run();
private:
    TaskQueue &_taskQue;
};

}
