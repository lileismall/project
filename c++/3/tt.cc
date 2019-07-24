#include <iostream>
using namespace std;


class tt
{
public:
    tt() :_a(0){}
    void set()
    {
        _a++;
    }
    void print()
    {
        cout << _a << endl;
    }
    private:
        int _a;
};


int main()
{
    tt t;
    t.set();
    t.print();
    return 0;
}

