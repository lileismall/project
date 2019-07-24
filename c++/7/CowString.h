


#include <string.h>

#include <iostream>
using namespace std;


class CowString
{
public:

    class CharProxy
    {
    public:
        CharProxy(CowString &self,int idx)
        : _self(self)
        , _idx(idx)
        {}

        char &operator=(const char &ch);
        friend ostream &operator<<(ostream &os,const CharProxy &rhs);//<<操作符只能定义为非成员友元函数
    
    private:
        CowString &_self;
        int _idx;
    };



    CowString();
    CowString(const char *pstr);
    CowString(const CowString &rhs);

    void initRefount();
    void increaseRefount();
    void decreaseRefount();
    void relese();
    int refount()const;

    CowString &operator=(const CowString &rhs);
    CharProxy operator[](int idx);
   // const char &operator[](int idx) const
   // {
   //     return _pstr[idx];
   // }

    friend ostream &operator<<(ostream &os,const CharProxy &rhs);

    ~CowString(){}

    int size() const;
    const char *c_str()const;
    

private:
    char *_pstr;
};
