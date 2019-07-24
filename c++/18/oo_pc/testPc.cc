
#include "Thread.h"
#include "TaskQueue.h"
#include "Pc.h"
#include <unistd.h>

#include <memory>

using namespace ll;
using namespace std;

int main()
{
    TaskQueue taskQue(2); //默认为10
    unique_ptr<Thread> producer1(new Producer(taskQue));
    unique_ptr<Thread> producer2(new Producer(taskQue));
    unique_ptr<Thread> consumer1(new Consumer(taskQue));
    unique_ptr<Thread> consumer2(new Consumer(taskQue));

    producer1->star();
    producer2->star();
    consumer1->star();
    consumer2->star();

    producer1->join();
    producer2->join();
    consumer1->join();
    consumer2->join();

    return 0;
}

