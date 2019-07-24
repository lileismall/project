#include "pimpl.h"



using namespace std;


class Test::Impl
{
public:
    Impl(int data)
    : _data(data)
    {
        cout << "Impl()" << endl;
    }

    ~Impl()
    {
        cout << "~Impl()" << endl;
    }

    void printImpl()
    {
        cout << "_data = " << _data <<endl;
    }
private:
    int _data;
};

Test::Test(int a)
: _pimpl(new Impl(a))
{
    cout << "Test()" << endl;
}

Test::~Test()  //_pimp, 要手动释放
{
    cout << "~Test()" << endl;
    if(_pimpl)
        delete _pimpl;
}

void Test::print() const
{
    _pimpl->Impl::printImpl();
}
