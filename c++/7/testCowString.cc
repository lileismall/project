#include "CowString.h"

using namespace std;


int main()
{
    CowString test1 = "hello";  
    CowString test2 = test1;
    CowString test3;
    test3 = test1;

    cout << "test1' refcount = " << test1.refount() << endl;
    cout << "test2' refcount = " << test2.refount() << endl;
    cout << "test3' refcount = " << test3.refount() << endl;
    printf("test1's address is %p\n", test1.c_str());
    printf("test2's address is %p\n", test2.c_str());
    printf("test3's address is %p\n", test3.c_str());


    test1[0] = 'H';
    cout << "test1' refcount = " << test1.refount() << endl;
    cout << "test2' refcount = " << test2.refount() << endl;
    cout << "test3' refcount = " << test3.refount() << endl;
    printf("test1's address is %p\n", test1.c_str());
    printf("test2's address is %p\n", test2.c_str());
    printf("test3's address is %p\n", test3.c_str());

    cout << test2[0];
    cout << "test1' refcount = " << test1.refount() << endl;
    cout << "test2' refcount = " << test2.refount() << endl;
    cout << "test3' refcount = " << test3.refount() << endl;
    printf("test1's address is %p\n", test1.c_str());
    printf("test2's address is %p\n", test2.c_str());
    printf("test3's address is %p\n", test3.c_str());
}

