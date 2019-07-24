
#include "Pc.h"
#include "TaskQueue.h"
#include <unistd.h>

using namespace std;


namespace ll
{

Producer::Producer(TaskQueue &taskQueue)
        : Thread()
        , _taskQue(taskQueue) 
        {}
Producer::~Producer() {}

void Producer::run()
{
    srand(clock());
    int cnt = 10;
    while(cnt--)
    {
        int num = rand() % 10;
        _taskQue.push(num);
        cout <<"producer thread " << pthread_self() << " cnt = " << cnt
             << ": produce a number = " << num<< endl;
        sleep(1);
    }
}

Consumer::Consumer(TaskQueue &taskQueue)
    : _taskQue(taskQueue)
    {}

void Consumer::run()
{
    int cnt = 10;
    while(cnt--)
    {
        int num = _taskQue.pop();
        cout << "consumer thread " << pthread_self() << " cnt = " << cnt
            << ":  consume a number = " << num << endl;
        sleep(1);
    }
}

}
