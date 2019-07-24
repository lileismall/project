
#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

class Computer
{
public:
    void setBrand(const char *brand)
    {
        strcpy(_brand,brand);
    }
    void setPrice(double price)
    {
        _price=price;
    }
    void print()
    {
        cout << "brand:" << _brand <<endl
             << "price:" << _price <<endl;
    }

private:
    char _brand[20];
    double _price;
};

int main()
{
    Computer pc;
    pc.setBrand("huawei");
    pc.setPrice(8888);
    pc.print();
}

