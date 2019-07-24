

#include <iostream>

using namespace std;

class A
{
public:
    virtual void func1()
    { cout << "this is A::func1()" <<endl; }
    virtual void func2()
    { cout << "this is A::func2()" <<endl; }
    void func3()
    {
        func1();
        A::func1();
        cout << "this is A::func3()" <<endl; }

};

class B
/* : public A */
{
public:
    B()
    {
        func1();
    }
    void func1()
    { cout << "this is B::func1()" <<endl; }
    void func2()
    { cout << "this is B::func2()" <<endl; }
    void func3()
    { 
        this->func2();
        cout << "this is B::func3()" <<endl; }
    
};


class C
:public B
{
public:
    void func1()
    { cout << "this is C::func1()" <<endl; }
    void func2()
    { cout << "this is C::func2()" <<endl; }
    void func3()
    { cout << "this is C::func3()" <<endl; }

};

#if 0
void tt()
{
    C test;
    A *pa = &test;
    pa->func1();
    pa->func2();
    pa->func3();

    cout << endl;
    B *pb = &test;
    pb->func1();
    pb->func2();
    pb->func3();

    cout << endl;
    C *pc = &test;
    pc->func1();
    pc->func2();
    pc->func3();
    

}

void tt1()
{
    C test0;
    A &pa = test0;
    pa.func1();
    pa.func2();
    pa.func3();


}
#endif 

void tt2()
{
    C test0;
    B &pa = test0;
    pa.func1();
    pa.func2();
    pa.func3();
}

int main()
{
    tt2();
}
