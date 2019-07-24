#include <iostream>



using std::cout;
using std::endl;


class Condition
{
public:

    Condition();
    ~Condition();

    void wait();
    void notify();
    void notifyall();
private:
    pthread_cond_t _cond;
};

Condition::~Condition()
{
    pthread_cond_destroy(&_cond);
}

Condition::Condition()
{
    pthread_cond_init(&_cond,NULL);
}

void Condition::notify()
{
    pthread_cond_signal(&_cond);
}

void Condition::notifyall()
{

}




int main()
{
    
}

