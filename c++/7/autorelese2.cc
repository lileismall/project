#include <iostream>
#include <pthread.h>
using namespace std;


//单例对象自动释放方案2：
//atexit + pthread_once

class Singleton
{
public:

    static Singleton *getInstance()
    {
        //保证只执行一次
        pthread_once(&_once,init);
        return _pInstance;
    }

    static void init()
    {
        _pInstance = new Singleton();
        atexit(destroy);
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
    static pthread_once_t _once;
};

Singleton *Singleton::_pInstance = getInstance(); // 饱汉模式
/* Singleton *Singleton::_pInstance = NULL; // 懒（饿）汉模式 */

pthread_once_t Singleton::_once = PTHREAD_ONCE_INIT;

int main()
{
    Singleton *p = Singleton::getInstance();
    return 0;
}

