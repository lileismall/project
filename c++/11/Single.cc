
#include <iostream>
#include <string>
#include "Point3.h"

using namespace std;

template <class Type>
class Single
{
private:
    Type _data;
    static Single* _pIntance;
    Single() {}
    Single(Type data) : _data(data) {}
    ~Single() {}

public:
    template <class... Args>
    static Single* getPintance(Args... args)
    {
        if(_pIntance == NULL)
        {
            _pIntance = new Single(Type(args...));
        }

        return _pIntance;
    }

    void set(Type data)
    {
        _data = data;
    }

    void destroy()
    {
        if(_pIntance)
        {
            delete [] _pIntance;
            _pIntance = NULL;
        }
    }

    Type get()
    {
        return _data;
    }

    void print()
    {
        cout << _data << endl;
    }
};
template <class Type>
Single<Type> *Single<Type>::_pIntance = NULL;

int main()
{
   /* Single<string> *p = Single<string>::getPintance(); */
   Single<Point> *p = Single<Point>::getPintance(1,2);
    p->get().print();
    /* p->print(); */

    return 0;
}

