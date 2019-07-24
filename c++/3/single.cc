#include <iostream>
using namespace std;


//单例设计模式




class Singleton
{
public:
    //定义一个返回值为此类的指针的静态成员函数
    static Singleton *getInstance()
    {
        if(_pInstance == NULL)
        {
            _pInstance=new Singleton();
        }
        return _pInstance;
    }

    void setData(int data)
    {
        _data=data;
    }

    static void destroy()
    {
        if(_pInstance)
        {
            delete _pInstance;
        }
    }

    void print() const
    {
        cout << "Singleton::data = " << _data << endl;
    }

    ~Singleton() { cout << "this is 析构函数" <<endl; }
private:
    //构造函数和析构函数私有化
    Singleton(): _data(0){ cout << "this is 私化的构造函数" << endl; }

private:
    int _data;
    static Singleton *_pInstance;
};

Singleton * Singleton::_pInstance = NULL;


int main()
{
    Singleton *p1=Singleton::getInstance();
    //Singleton :: getInstance()->print();
    p1->print();
    Singleton *p2=Singleton::getInstance();
    p1->setData(1);
    p1->print();
    p2->setData(2);
    p2->print();

    p1->destroy();
}

