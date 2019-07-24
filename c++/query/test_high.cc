

#include "query_high.h"


using namespace std;


void test0()
{
    ifstream os("file");
    TextQuery test(os);
    Query q = ~Query("are");  //用基类指向派生类

    print(cout,q.eval(test));

}

void test1()
{
    ifstream os("file");
    TextQuery test(os);
    Query q= Query("how") & Query("you");

    print(cout,q.eval(test));
}

int main()
{
    test1();

    return 0;
}
