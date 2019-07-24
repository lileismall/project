
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <iterator>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_set>

using namespace std;

template <class T>
void print(T t)
{
    for(auto &s : t)
    {
        cout << s.first << ":" << s.second <<endl;
    }
}

template <class T>
void print1(T t)
{
    for(auto &s : t)
    {
        cout << s << " ";
    }
    cout << endl;
}


void test0()
{
    unordered_map<int,int> t{
        {1,1},
        {2,2},
        {3,3}
    };
}

void test1()
{
    map<int,int> m;
    m[1] = 1;
    m[2] = 2;

    auto mm = m.insert(pair<int,int>(3,3));
    cout << (*mm.first).first << " " << mm.second << endl;
    m.insert(make_pair(4,4));
    print(m);
}

void test2()
{
    vector<int> v={1,2,3,4,5};
    vector<int> vc={1,2,3,4,5};
    v.insert(v.begin()+2,vc.begin(),vc.begin()+2);
    print1(v);
}

void test3()
{
    map<int,int,greater<int>> m;
    m[1] = 1;
    m[2] = 2;
    m[3] = 3;
    m[2] = 4;
    m[2] = 5;
    vector<string> n;
    string s = "124"
        "234"
        "545\n"
        "465";
    cout << s << endl;
    n.push_back("ff");
    n.push_back("2f");
    ostream_iterator<string> test(cout," ");
    copy(n.begin(),n.end(),test);
    for(auto &s : m)
    {
        cout << s.second << endl;
    }
    /* auto res = m.insert(make_pair(3,3)); */
}

void test4()
{
    unordered_map<int,int> unm;   
    unm[1] = 1;
    unm[3] = 3;
    unm[2] = 2;
    for(auto &s : unm)
    {
        cout << s.first << "-->" << s.second << endl;
    }

}
int main()
{
    test4();
}

