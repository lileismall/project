#include <iostream>
#include <string.h>
#include <string>
using namespace std;

class String
{
public:
    //构造函数
    String()
    {
        _ptr=new char[5](); //默认申请五个字节
        cout << "this is 无参构造函数" << endl;
    }
    String(const char *ptr)
    : _ptr(new char[strlen(ptr)+1])
    {
        strcpy(_ptr,ptr);
        cout << "this is 有参构造函数" << endl;
    }
    //复制构造函数
    String(const String & rhs)
    : _ptr(rhs._ptr)
    {
        cout << "this is 复制构造函数" << endl;
    }

    //赋值运算符函数  operaor 操作者
    String &operator=(const String &rhs)
    {
        delete [] _ptr;
        _ptr=new char[strlen(rhs._ptr)+1]();
        strcpy(_ptr,rhs._ptr);
         cout << "this is 赋值运算符函数" << endl;
         return (*this);
    }

    //析构函数
    ~String()
    {
        delete [] _ptr;
        cout << "this is 析构函数" << endl;
    }
    //打印
    void print()
    {
        cout << "ptr = " << _ptr <<endl;
    }
private:

    char *_ptr;

};


int main()
{
    String str1;
    str1.print();

    String str2=("hello");
    String str3("wangdao");

    str2.print();
    str3.print();

    String str4=str3;
    str4.print();

    str4=str2;
    str4.print();
}

