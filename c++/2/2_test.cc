
#include <string.h>
#include <iostream>

using std::cout;
using std::endl;
//类的外部定义成员函数
class Computer
{
public:
    void setBrand(const char *brand);
    void setPrice(double price);
    void print();

private:
    char _brand[20];
    double _price;
};

void Computer::setBrand(const char *brand)
{
    strcpy(_brand,brand);
}
void Computer::setPrice(double price)
{
    _price=price;
}
void Computer::print()
{
    cout << "brand:" << _brand <<endl
        << "price:" << _price <<endl;
}
int main()
{
    Computer pc;
    pc.setBrand("huawei");
    pc.setPrice(8888);
    pc.print();
}

