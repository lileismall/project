#include <iostream>
using namespace std;

class point //类定义
{
    int x; //默认private型成员变量x和y
    int y;

public:
    point(int xp = 0, int yp = 0)//构造函数
    {
        x = xp;
        y = yp;
    }

    ~point()                    //析构函数
    {
        x = -1;
    }

    void SetX(int xp) //非const成员函数SetX，设置x
    {
        x = xp;
    }

    void SetY(int yp) //非const成员函数SetY，设置y
    {
        y = yp;
    }

    void print() const //const成员函数print，不能修改x和y
    {
        cout << "x: " << x << " ,y: " << y << endl;
    }
};


int main()
{
    point pt(3, 4);         //声明一个普通类变量pt
    pt.SetX(5);             //使用pt可调用非const成员函数
    pt.SetY(6);
    pt.print();             //pt也可调用const成员函数

    const point ptC(1, 2);  //声明一个const对象（类变量）
    //ptC.SetX(8);          //错误，ptC是const对象，只能调用const成员函数
    //ptC.SetY(9);          //错误，ptC是const对象，只能调用const成员函数
    ptC.~point();           //正确，const对象也能调用非const类型的析构函数
    ptC.print();            //正确，const对象只能调用const成员函数

    return 0;
}

