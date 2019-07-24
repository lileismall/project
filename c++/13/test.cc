
#include <iostream>
#include <list>

using namespace std;

void print(list<int> &s)
{
    for(auto &a : s)
    {
        cout << a << " ";
    }
    cout << endl;
}

void  main1()
{
    list<int> s1 = {1,2,3};
    print(s1);

    list<int> s2 = {11,22,33};
    s1.insert(s1.begin(),--s1.end(),s1.end());
    print(s1);
    print(s2);
}

void test1()
{
    list<int> s1 = {1,2,3};
    s1.emplace(++s1.end(),int(4));
    print(s1);

}

int main()
{
    test1();
}

