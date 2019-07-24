
#include <iostream>
#include <memory>
#include <algorithm>

using namespace std;

template <class Type>
class Vector
{
public:
    using iterator = Type *;
    using const_iterator = const Type *;

    Vector()
    : _start(NULL)
    , _finish(NULL)
    , _end(NULL)
    {}

    ~Vector()
    {
        if(_start)
        {
            while(_finish != _start)
            {
                _alloc.destroy(--_finish);
            }
            _alloc.deallocate(_start,capacity());
        }
    }

    size_t size() const {return _finish - _start; }
    size_t capacity() const  {return _end - _start; }

    void push_back(const Type & value) ;
    void pop_back();

    iterator begin() { return _start; }
    iterator end() {return _finish; }

    Type &operator[](size_t idx) { return _start[idx];  }

private:
    void reallocate();
    static allocator<Type> _alloc;
    Type * _start;
    Type * _finish;
    Type * _end;
};

template <class Type>
allocator<Type> Vector<Type>::_alloc;

template <class Type>
void Vector<Type>::push_back(const Type & value)
{
    if(size() == capacity())
    {
        reallocate();
    }
    _alloc.construct(_finish++,value);
}

template <class Type>
void Vector<Type>::pop_back()
{
    if(size())
    {
        _alloc.destroy(--_finish);
    }
}

template <class Type>
void Vector<Type>::reallocate()  //重点
{
    size_t capa = capacity();
    size_t newcapa = 2*capa > 0 ? 2*capa : 1;
    Type *p = _alloc.allocate(newcapa);
    if(_start)
    {
        uninitialized_copy(_start,_finish,p);
        while(_start != _finish)
        {
            _alloc.destroy(--_finish);
        }
        _alloc.deallocate(_start,capa);
    }
    _start = p;
    _finish = _start + capa;
    _end = _start + newcapa;
}

int main()
{
    Vector<int> i;
    i.push_back(1);
    i.push_back(2);
    i.push_back(3);
    i.push_back(4);
    i.push_back(5);
    for(auto &s : i)
    {
        cout << s << " ";
    }
    cout << endl;

    cout << i[2] << endl;
    return 0;
}

