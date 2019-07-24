
#include "Thread.h"

#include <unistd.h>
#include <time.h>
#include <iostream>
#include <memory>

using namespace ll;
using namespace std;

class myThread
:public Thread
{
    void run()
    {
        srand(clock());
        int cnt = 10;
        while(cnt--)
        {
            int num = rand() % 10;
            cout << "pthread " << pthread_self()
                << " num : " << num <<endl;
        }
    }
};

int main()
{
    unique_ptr<Thread> thread(new myThread());
    thread->star();
    sleep(1);
}
