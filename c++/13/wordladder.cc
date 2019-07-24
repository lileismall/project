
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Singchar //找到与当前单词只差一个字母的单词
{
public:
    
private:
    unordered_map<int,string> _unm;

};

template <class T>
void print(T data)
{
    for(auto &s : data )
    {
        cout << s.first << ":" << s.second <<endl;
    }
}

int main()
{
    unordered_map<int,string> s;

    s[2] = "string";
    s[4] = "tst";
    cout << s[1];
    print(s);
}

