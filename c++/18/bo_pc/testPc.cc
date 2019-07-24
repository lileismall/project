
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
    unique_ptr<Thread> producer1(new Thread(
                bind(&Producer::produce,Producer(),ref(taskQue ))
                ));
    unique_ptr<Thread> producer2(new Thread(
                bind(&Producer::produce,Producer(),ref(taskQue ))
                ));
    unique_ptr<Thread> consumer1(new Thread(
                    bind(&Consumer::consume,Consumer(),ref(taskQue))
                ));
    unique_ptr<Thread> consumer2(new Thread(
                    bind(&Consumer::consume,Consumer(),ref(taskQue))
                ));

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

