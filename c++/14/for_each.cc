
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

void print(int num)
{
    cout << num << endl;
}

/* template <class T> */
class Print
{
public:
    template <class T>
    void operator()(T num)
    {
        cout << num << endl;
    }
};

int main()
{
    vector<string> test = {"aa","bb"};
    /* for_each(test.begin(),test.end(),[](int num) {cout << num << endl; }); */
    Print p;
    for_each(test.begin(),test.end(),p);

    return 0;
}

