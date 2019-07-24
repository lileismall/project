#include "stack.h"

//using namespace std;

using std::cout;
using std::endl;

Stack::Stack()
: _size(10)  //栈的大小默认为10
, _i(0)
, _top(NULL)
//, _tail(NULL)
{
    cout << "this is 构造函数" << endl;
}

Stack::~Stack()
{
    pNode pnode;
    int j=0;
    while(_i)
    {
        pnode = _top;
        _top = _top->Next;
        _i--;
        delete pnode;
        pnode = NULL;
        j++;
    }
    cout << "已经清除了"<< j <<"个结点" << endl;
}


void Stack::setSize(int size) //设置栈的大小
{
    _size=size;
}

bool Stack::full()
{
    if(_i < _size)
        return false;  //没满
    return true;
}

bool Stack::empty()
{
    if(_i)
        return false; 
    return true;// 为空返回真
}


void Stack::push(datatype data)
{
    if(!full())
    {
        pNode pnode=new Node;
        pnode->data = data;
        pnode->Next = _top;
        _top= pnode;
        _i++;
    }
    else
        cout << "栈已满" <<endl;
}

void Stack::pop()
{
    if(!empty()) //如果不为空
    {
        pNode pnode=_top;
        _top = _top->Next;
        delete pnode;
        _i--;
    }else{
        cout << "栈为空" <<endl;
    }
}

int Stack::top()
{
    return _top->data;
}










