#include <iostream>

#include "String.h"

using namespace std;
using namespace ll;
int main()
{
    String test1("test");
    String test4="hello";
    
    if(test4 < test1)
        cout << "test4 < test1" <<endl;
    else
        cout << "test4 !< test1" <<endl;


    String test2;
    String test3;
    test2=test1;

    if(test2==test1)
        cout << "相等" <<endl;
    else
        cout << "不相等" <<endl;



    test2 += test1;
    test2 += "ll";

    test1.print();
    test2.print();

    cout << "----------------------" << endl;
    cout << test1 << endl;

    cin >> test1 ;
    cout << test1 << endl;



    cout << test2[3] <<endl;

    return 0;
}

