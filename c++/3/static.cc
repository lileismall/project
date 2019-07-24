#include <iostream>
using namespace std;


class test
{
private:
    int _a,_b;
    static int _c;

public:
    test(const int a): _a(a)
    {
        _c += _a;
    }

    void print()
    {
        cout << "_a = " << _a
             << "_c = " << _c << endl;
    }

    ~test()
    {
        _c -= _a;
        cout << "this is 析构函数" << endl;
    }
};

int test:: _c=0;

int main()
{
    test computer1(22);
    computer1.print();
    test computer2(33);
    computer2.print();
    computer1.~test();
    computer2.print();

    return 0;
}

