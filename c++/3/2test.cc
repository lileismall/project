#include <iostream>
using namespace std;


class TestConst
{
private:
    const int _a;

public:
    TestConst(int a) : _a(a)
    {
        cout << "this is 构造函数" << endl;
    }


    TestConst(const TestConst &rhs) : _a(rhs._a)
    {
    }

    void print() const
    {
        cout << "TestConst :: a = " << _a << endl;
    }
};


int main()
{
    TestConst test1(3);
    TestConst test2(test1);
    test1.print();
    test2.print();

    return 0;
}

