#include "stack.h"

//using namespace std;



int main()
{
    Stack s;
    s.setSize(5); //默认是10
    s.push(10);
    s.push(12);
    s.push(14);
    s.printTop();
    s.pop();
    s.printTop();
    return 0;
}

