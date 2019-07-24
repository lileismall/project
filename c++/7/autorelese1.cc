#include <iostream>
using namespace std;


//单例对象自动释放方案2：
//atexit + 静态方法

class Singleton
{
public:

    static Singleton *getInstance()
    {
        //多线程环境下，这里应该加锁，也可以用饱汉模式,
        if(_pInstance == NULL){
            _pInstance = new Singleton();
            atexit(destroy);
        }
        return _pInstance;
    }

    static void destroy()
    {
        if(_pInstance)
            delete _pInstance;
    }
private:
    Singleton(){cout << "Singleton()" << endl;}
    ~Singleton(){cout << "~Singleton()" << endl;}
    static Singleton *_pInstance;
};

Singleton *Singleton::_pInstance = getInstance(); // 饱汉模式
/* Singleton *Singleton::_pInstance = NULL; // 懒（饿）汉模式 */

int main()
{
    Singleton *p = Singleton::getInstance();
    return 0;
}

