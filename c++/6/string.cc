#include "String.h"

using namespace std;

namespace ll  //定义和声明一定要同一个命名空间里
{

String::String()
    : _pstr(new char[1]())
{
    
}

String::String(const char * ptr)
    : _pstr(new char[strlen(ptr)+1]())
{
    strcpy(_pstr,ptr);
}

String::String(const String & rhs)
    :_pstr(new char[strlen(rhs._pstr) + 1]())
{
    strcpy(_pstr,rhs._pstr);
}

String::~String()
{
    delete [] _pstr;
}

String &String::operator=(const String & rhs)
{
    if(&rhs != this)
    {
        delete [] _pstr;
    }
    _pstr = new char[strlen(rhs._pstr)+1]();
    strcpy(_pstr,rhs._pstr);
    return *this;
}

String &String::operator=(const char *pstr)
{
    delete [] this;
    _pstr = new char[strlen(pstr) + 1]();
    
    strcpy(_pstr,pstr);
    return *this;
}

String &String::operator += (const String & rhs)
{
    char *temp = new char[strlen(_pstr)+1]();
    strcpy(temp,_pstr);
    delete [] _pstr;
    _pstr = new char[strlen(temp) + strlen(rhs._pstr) + 1]();

    strcat(_pstr,temp);
    strcat(_pstr,rhs._pstr);

    /* _pstr.append(temp).append(rhs._pstr); */
    return *this;
}

String &String::operator+=(const char * pstr)
{
    char *temp = new char[strlen(_pstr)+1]();
    strcpy(temp,_pstr);
    delete [] _pstr;
    _pstr = new char[strlen(temp) + strlen(pstr) + 1]();

    strcat(_pstr,temp);
    strcat(_pstr,pstr);

    return *this;
}

char &String::operator[](std::size_t index)
{
    if(index > strlen(_pstr)){
        cout << "出界" << endl;
        static char nullchar = '\0';  //这为什么要加static
        return nullchar;
    }
    else
    {
        return _pstr[index];
    }
}

const char &String::operator[](std::size_t index) const
{
    if(index > strlen(_pstr)){
        cout << "出界" << endl;
        const static char nullchar = '\0';  //这为什么要加static
        return nullchar;
    }
    else
    {
        return _pstr[index];
    }
}

std::size_t String::size() const
{
    return strlen(_pstr);
}

const char* String::c_str() const
{
    return _pstr;
}

bool operator == (const String &lhs,const String &rhs)
{
    return !strcmp(lhs._pstr,rhs._pstr);
}

bool operator<(const String &lhs, const String &rhs)
{
    if(*lhs._pstr < *rhs._pstr)
        return true;
    else
        return false;
}


ostream &operator<<(std::ostream &os, const String &s)
{
    os << s._pstr ;
    return os;
}

istream &operator>>(std::istream &is,String &s)
{
    is >> s._pstr ;
    return is;
}


}// end of namespace ll
