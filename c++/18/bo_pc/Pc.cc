
#include "Pc.h"
#include "TaskQueue.h"
#include <unistd.h>

using namespace std;


namespace ll
{


void Producer::produce(TaskQueue &taskQue)
{
    srand(clock());
    int cnt = 10;
    while(cnt--)
    {
        int num = rand() % 10;
        taskQue.push(num);
        cout <<"producer thread " << pthread_self() << " cnt = " << cnt
             << ": produce a number = " << num<< endl;
        sleep(1);
    }
}


void Consumer::consume(TaskQueue &taskQue)
{
    int cnt = 10;
    while(cnt--)
    {
        int num = taskQue.pop();
        cout << "consumer thread " << pthread_self() << " cnt = " << cnt
            << ":  consume a number = " << num << endl;
        sleep(1);
    }
}

}
