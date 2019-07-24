

#include <iostream>


using namespace std;

class A
{
    int i;
    virtual void func1() = 0;
    virtual void func2() = 0;
    virtual void func3() = 0;
    virtual void func4() = 0 ;
    virtual void func5() = 0 ;
};

class C
:public A
{
public:
    virtual void func1() {}
    virtual void func2() {}
    virtual void func3() {}
    virtual void func4() {}
    virtual void func5() {}
};
class B
:virtual public C
{
    virtual void func1() {}
    virtual void ff() {}
};

void func();
int main()
{
    C test;
    test.func2();

}

