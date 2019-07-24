
#include <iostream>

using namespace std;

template <class Type,int kSize = 10> 
class Queue
{
private:

    int _front,_rare;
    Type *_base;

public:
    Queue()
    : _front(0)
    , _rare(0)
    , _base(new Type[kSize]())
    {}

    ~Queue()
    {
        if(_base)
            delete [] _base;
    }

    bool full() const;
    bool empty() const;
    void push(const Type &value);
    void pop();
    const Type &top() const;
};

template <class Type,int kSize> 
bool Queue<Type,kSize>::full() const
{
    /* return (_rare + 1)%kSize == _front; */  
    return (_front + 1)%kSize == _rare;
}

template <class Type,int kSize> 
bool Queue<Type,kSize>::empty() const
{
    return _rare == _front;
}

template <class Type,int kSize> 
void Queue<Type,kSize>::push(const Type &value)
{
    if(!full())
    {
        cout << "添加了一个元素：" << value << endl;
        _base[_front++] = value;
        if(_front >= 10)
            _front = _front%10;
        
    }else{
        cout << "队列为已满" << endl;
    }
}

template <class Type,int kSize> 
void Queue<Type,kSize>::pop()
{
    if(empty())
    {
        cout << "队列为空" << endl;
    }else{
        cout << "pop出一个" << _base[_rare] <<endl;
        ++_rare;
        if(_rare >= 10)
            _rare = _front%10;
    }
}

template <class Type,int kSize> 
const Type &Queue<Type,kSize>::top() const
{
    return _base[_rare];   
}

int main()
{
    Queue<int> test;
    cout << "队列是否为空？" << test.empty() << endl;
    
    test.push(3);
    test.push(4);
    for(int i=1; i < 12 ;i++)
    {
        test.push(i);
    }

    cout << "队列是否为空？" << test.empty() << endl;
    cout << "队列是否已满？" << test.full() << endl;

    test.pop();
    cout << "队列是否已满？" << test.full() << endl;

    return 0;
}










