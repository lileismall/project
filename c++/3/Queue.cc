#include "Queue.h"
//using namespace std;
//


using  std::cout;
using  std::endl;


int main()
{
    Queue que;
    que.setSize(5);  //默认为5
    que.push(10);
    que.push(12);
    que.push(14);
    que.pop();

    cout << "frant = " <<que.front() << endl;
    cout << "rear = " <<que.back() << endl;
    return 0;
}

