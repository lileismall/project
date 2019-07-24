#include <iostream>



using namespace std;

class test
{
    int _a=10;
public:
    friend int tt(const test &a);
    friend bool operator+ (const test &a,const test &b);
};

int tt(const test &a)
{
    int b=a._a;
    return b;
}

bool operator+(const test &a,const test &b)
{
    return a._a + b._a;
}

int main()
{
    test t;
    int e=tt(t);
    cout << e << endl;
    return 0;
}

