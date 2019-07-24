#pragma once

#include <string.h>

#include <iostream>
#include <string>


namespace ll
{

class String {
public:
    String();
    String(const char *);
    String(const String&);
    ~String();
    String &operator=(const String &);
    String &operator=(const char *);

    String &operator+=(const String &);
    String &operator+=(const char *);

    char &operator[](std::size_t index);
    const char &operator[](std::size_t index) const;

    std::size_t size() const;
    const char* c_str() const;

    friend bool operator==(const String &,const String &);
    friend bool operator!=(const String &, const String &);

    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator>=(const String &, const String &);

    friend std::ostream &operator<<(std::ostream &os, const String &s);
    friend std::istream &operator>>(std::istream &is, String &s);

    void print() const
    {
        std::cout << _pstr << std::endl;
    }

private:
    char * _pstr;

};

String operator+(const String &, const String &);
String operator+(const String &, const char *);
String operator+(const char *, const String &);

}//end of namespace ll

/* using namespace ll; */

