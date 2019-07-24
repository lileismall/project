#include <iostream>
using namespace std;

//实验：
//程序结束释放堆空间时是否会调用析构函数

class test
{
private:
    int *a;

public:

    test() {    cout << "test()" <<endl;  }

    test(int *b) : a(b)
    {
        cout << "test(int *)" <<endl;
    }
    ~test()
    {
        cout << "~test()" << endl;
    }
};


int main()
{
    int b=5;
    test *tt = new test(&b);
    test *tr = new test();
    return 0;
}

