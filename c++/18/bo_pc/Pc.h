#pragma once
#include "Thread.h"

namespace ll
{

class TaskQueue;

class Producer
{
public:
    Producer() {}
    ~Producer() {}
    
    void produce(TaskQueue &taskQueue);
};

class Consumer
{
public:
    Consumer(){}
    ~Consumer(){}

    void consume(TaskQueue &taskQueue);
};

}
