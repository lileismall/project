#pragma once

#include <iostream>

using std::cout;
using std::endl;;

typedef int datatype;

typedef struct node{
    datatype data;
    struct node *Next;
}Node,*pNode;

class Stack
{
public:
    Stack();
    ~Stack();

    void push(datatype);
    void pop();
    int top();
    bool empty();
    bool full();
    void setSize(int);
    void printTop()
    {
        cout << "top of stack = " << _top->data <<endl;
    }

private:
    int _size;  //栈的大小
    int _i;     //用来判断栈的满空
    pNode _top;
    //pNode _tail;
};

