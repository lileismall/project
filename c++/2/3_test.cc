
#include <string.h>
#include <iostream>

using std::cout;
using std::endl;
//类的外部定义成员函数
class Computer
{
public:
    Computer(const char *brand,double price)//构造函数
    : _brand(new char[strlen(brand)+1]())
    , _price(price)
    {
        strcpy(_brand,brand);
        cout << "Computer(const char *,double)" <<endl;
    }
    ~Computer() //析构函数
    {
        delete [] _brand;
        _brand = NULL;
        cout << "this is ~Computer" << endl;
    }
    void setBrand(const char *brand);
    void setPrice(double price);
    void print();

private:
    char *_brand;
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



void test1()
{
    Computer pc1("huawei",8888);
    pc1.print();
}
int main()
{
    Computer pc("xiaomi",6666);
    pc.print();
    pc.setBrand("huaweibook");
    pc.setPrice(8888);
    pc.print();
}

