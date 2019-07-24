
#include <iostream>
#include <deque>

using namespace std;

int main()
{
    deque<int,int> test(2,3);
    test.push_back(1);
    for(auto &s : test)
    {
        cout << s << " ";
    }
    cout << endl;
    return 0;
}

