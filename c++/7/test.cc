#include <iostream>
#include <string.h>
using namespace std;


class test
{
public:
    test(const char *pstr)
    : _pstr(new char[strlen(pstr) + 1])
    {
        strcpy(_pstr,pstr);
    }
    test operator=(const char *pstr)
    {
        delete [] this;   
        _pstr = new char[strlen(pstr) + 1] ();
        strcpy(_pstr,pstr);
        return *this;
    }

    char operator[](int i)
    {
        return _pstr[i];
    }

private:
        char *_pstr;
};



int main()
{
    /* test a = "hello"; */
    /* test a("hello"); */
    test aa = "kk";
    cout << aa[0] << endl;
    return 0;
}

