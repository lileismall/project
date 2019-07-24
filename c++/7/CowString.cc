
#include "CowString.h"

CowString::CowString()
: _pstr(new char[1 + 4] +4)
{
    cout << "CowString()" <<endl;
    initRefount();
}

CowString::CowString(const char *pstr)
: _pstr(new char[strlen(pstr) + 5] + 4)
{
    cout << "Cowstring(const char *pstr)" <<endl;
    initRefount();
    strcpy(_pstr,pstr);
}

CowString::CowString(const CowString &rhs)
: _pstr(rhs._pstr)
{
    cout << "CowString(const CowString &rhs)" << endl;
    increaseRefount();
}

CowString &CowString::operator=(const CowString &rhs)
{
    cout << "CowString & operator=(const CowString &)" <<endl;
    if(this != &rhs)
    {
        relese();

        _pstr = rhs._pstr;
        increaseRefount();
    }
    return *this;
}


//工具函数
void CowString::initRefount()
{
    *(int*)(_pstr - 4) = 1;
}

void CowString::increaseRefount()
{
   ++*(int *)(_pstr -4);
}

void CowString::decreaseRefount()
{
    --*(int *)(_pstr -4);
}

int CowString::refount() const
{
    return *(int*)(_pstr - 4);
}

void CowString::relese()
{
    decreaseRefount();
    if(refount() == 0)
    {
        delete [] (_pstr - 4);
        cout << ">> delete heap data!" << endl;
    }
}

int CowString::size()const
{
    return strlen(_pstr);
}

const char *CowString::c_str() const
{
    return _pstr;
}


CowString::CharProxy CowString::operator[](int idx)
{
    return CharProxy(*this,idx);
}

char &CowString::CharProxy::operator=(const char &ch)
{
    cout << "_idx = " <<_idx<<endl;
    cout << "_self.size() = " <<_self.size()<<endl;
    cout << "_self._pstr" << _self._pstr <<endl;

    if(_idx >= 0 && _idx < _self.size())
    {
        if(_self.refount() > 1)
        {
            _self.decreaseRefount();

            char *ptmp = new char[strlen(_self._pstr) + 5] +4;
            strcpy(ptmp,_self._pstr);
            _self._pstr = ptmp;
            _self.initRefount();
        }
        _self._pstr[_idx] = ch;
        return _self._pstr[_idx];
    }
    else
    {
        static char nullchar = '\0';
        cout << "下标越界" << endl;
        return nullchar;
    }
}

ostream &operator<<(ostream &os,const CowString::CharProxy &rhs)
{
    os << rhs._self._pstr[rhs._idx];
    return os;
}
