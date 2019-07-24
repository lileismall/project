#include <iostream>

using namespace std;

class Circle
{
private:
    int _r;
public:
    Circle()
    : _r(0)
    {}

    Circle(int r)
    : _r(r)
    {}

    int getArea()
    {
        return 3*_r*_r;
    }

    int getPerimeter()
    {
        return 6*_r;
    }

    void show()
    {
        cout << "半径r：" << _r <<endl;
        cout << "面积s：" << getArea() <<endl;
        cout << "周长c：" << getPerimeter() <<endl;
    }

};

class Cylinder
: public Circle
{
private:
    int _h;
public:
    Cylinder (double r, double  h)
    : Circle(r)
    , _h(h)
    {}

    int getVolume()   //获取圆柱体的体积             
    {
        return getArea()*_h;
    }

    void  showVolume()   //将圆柱体的体积输出到屏幕
    {
        cout << "volume V:"<<getVolume() << endl;
    }
};



int main()
{
    Cylinder test2(2,3);
    test2.Circle::show();
    test2.showVolume();
    return 0;
}

