
#include "Threadpoll.h"
#include "Task.h"

#include <unistd.h>
#include <iostream>

using namespace std;
using namespace ll;

class MyTask
:public Task
{
public:
    void process()
    {
        ::srand(::clock());
        int number = ::rand() % 100;
        cout << ">>> sub Thread " << pthread_self()
            << " Mytask: number = " << number << endl;
        /* ::sleep(1); */
    }
};

int main()
{
    unique_ptr<Task> task(new MyTask());
    Threadpoll threadpoll;
    threadpoll.start();

    int cnt = 10;
    while(cnt--)
    {
        threadpoll.addTask(task.get()); //get() 是unique<Task> 的方法
        cout << "main thread " << pthread_self()
            << ": cnt = " << cnt << endl;
    }
    threadpoll.stop();
}

