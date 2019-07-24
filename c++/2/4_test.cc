
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
        cout << "this is 构造函数" <<endl;
    }
    //复制函数,const 和 & 不能省
    Computer(const Computer & rhs)
    : _brand(new char[strlen(rhs._brand)+1])
    , _price(rhs._price)
    {
        strcpy(_brand,rhs._brand);
        cout << "this is 复制函数" << endl;
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
    Computer pc("xiaomiBook",6666);
    Computer pc2=pc;
    pc2.print();
    pc.setBrand("huawei");
    pc.setPrice(8888);
    pc.print();
}

