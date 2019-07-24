#include "Queue.h"
//ueing namespace std;
//

using std::cout;
using std::endl;

Queue::Queue()
    : _size(10)
    , _i(0)
    , _front(new Node)
    , _rear(_front)
{
    cout << "this is 构造函数" << endl; 
}

Queue::~Queue()
{
    pNode pnode;
    int i=0;
    while(_i)
    {
        pnode=_front;
        _front = _front->pNext;
        delete pnode;
        _i--;
        i++;
    }
    cout << "已经清除了" << i << "个结点" << endl;
}



bool Queue::empty()
{
    if(_i==0)
    {
        cout << "队列为空" << endl;
        return true;
    }
    return  false;
}

bool Queue::full()
{
    if(_i==_size)
    {
        cout << "队列已满" <<endl;
        return true;
    }
    return false;
}

void Queue::push(datatype data)
{
    if(!full())
    {
        pNode pnode =new Node;
        pnode->data=data;
        pnode->pNext = NULL;

        _rear->pNext = pnode;
        if(empty())
        {
            _front->pNext = pnode;
            _front=pnode;
        }
        _rear = pnode;
        _i++;
    }
}

void Queue::pop()
{
    if(!empty())
    {
        pNode pnode=_front;
        _front = _front->pNext;
        delete pnode;
        pnode = NULL;
        _i--;
    }
}

int Queue::front()
{
    if(!empty())
    {
        return _front->data;
    }
    return -1; //-1代表队列为空
}

int Queue::back()
{
    if(!empty())
    {
        return _rear->data;
    }
    return -1;
}
