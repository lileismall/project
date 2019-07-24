#include <iostream>



using namespace std;

class Data
{
public:
    Data(int data=1)
    : _data(data)
    {
        cout << "Data()" << endl;
    }

    void print()const
    {
        cout << "data = " << _data << endl;
    }

    ~Data()
    {
        cout << "~Data()" << endl;
    }

private:
    int _data;
};

class Mid
{
private:
    Data *_pdata;
public:
    Mid(Data *pdata)
    : _pdata(pdata)
    {
        cout << "Mid()" << endl;
    }

    Data * operator ->()
    {
        return _pdata;
    }

    Data & operator *()
    {
        return *_pdata;
    }

    ~Mid()
    {
        cout << "~Mid()" <<endl;
        if(_pdata)
            delete _pdata;
    }
};

int main()
{
    /* Data data; */
    Mid test(new Data(10));

    test->print();
    (*test).print();

    return 0;
}

