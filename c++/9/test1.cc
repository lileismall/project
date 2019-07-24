#include <iostream>
using namespace std;

class A
{
public:
    virtual void print()
    {
        cout << "this is A" << endl;
    }
};

class B
:public A
{
    void print()
    {
        cout << "this is B" << endl;
    }
};

int main()
{
    A *test = new B();
    test->print();
    return 0;
}

