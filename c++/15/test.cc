
#include <vector>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <map>
#include <memory>
#include <cctype>

using namespace std;

void test0()
{
    allocator<int> test;
    auto p = test.allocate(2);
    multimap<int,int> t;
    /* map<int,int> tt; */
    t.insert(make_pair(1,1));
    t.insert(make_pair(2,2));
    t.insert(make_pair(1,2));
    auto te = t.equal_range(1);
    /* t.insert(2,2); */
    /* t.insert(1,2); */
    cout << distance(t.lower_bound(1),t.upper_bound(1))<<endl;

    /* auto it = t.lower_bound(1); */
    auto iter = te.first;
    while( iter != te.second)
    {
        cout << "t[1] = " <<  iter->second <<endl;
        ++iter;
    }
    printf("p = %p",p);
}

void test1()
{
    string s = "hello";
    s[1] = toupper(s[1]);
    s[1] = toupper(s[1]);
    cout << s << endl;
}

void test2()
{
    vector<int> vv = {1,2,3,4,5,6,7,8} ;  
    /* int max = 4; */
    int ss = 6;
    auto it = search_n(vv.begin(),vv.end(),3,4,[ss](int s,int max){cout << ss <<endl;return s > max;});
    cout << *it <<endl;
    
}
/* int main() */
/* { */
    /* string s = "jianshe"; */
    /* auto it = s.begin(); */
    /* it = it + 2; */
    /* advance(it,2); */
    /* test1(); */
    /* return 0; */
/* } */

int main()
{
    test2();
}
