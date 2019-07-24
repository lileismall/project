#pragma once

#include <iostream>
typedef int datatype;

typedef struct node{
    datatype data;
    node *pNext;
}Node,*pNode;


class Queue
{
public:
    Queue();
    ~Queue();
    void setSize(int size)
    {
        _size=size;
    }

    void push(datatype);
    void pop();
    int front();
    int back();
    bool empty();
    bool full();

private:
    int _size;
    int _i;
    pNode _front;
    pNode _rear;
};

