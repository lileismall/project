#include <iostream>
using namespace std;


//单例对象自动释放方案1：
//嵌套类 + 静态对象

class Singleton
{
public:

    class AutoRelese
    {
    public:
        AutoRelese(){ cout << "AutoRelese()" <<endl; }
        ~AutoRelese()
        {
            if(_pInstance)
                delete _pInstance;
            cout << "~AutoRelese()" <<endl;
        }
    };

    static Singleton *getInstance()
    {
        //多线程环境下，这里应该加锁，也可以用饱汉模式,
        if(_pInstance == NULL)
            _pInstance = new Singleton();
        return _pInstance;
    }

    void destroy()
    {
        if(_pInstance)
            delete _pInstance;
    }
private:
    Singleton(){cout << "Singleton()" << endl;}
    ~Singleton(){cout << "~Singleton()" << endl;}
    static Singleton *_pInstance;
    static AutoRelese _auto;
};

Singleton *Singleton::_pInstance = getInstance(); // 饱汉模式
/* Singleton *Singleton::_pInstance = NULL; // 懒（饿）汉模式 */

Singleton::AutoRelese _auto;

int main()
{
    Singleton *p = Singleton::getInstance();
    return 0;
}

