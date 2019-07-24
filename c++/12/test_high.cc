
#include "query_high.h"


using namespace std;


void test0()
{
    ifstream is("china_daily.txt");
    string word;

    cin >> word;
    TextQuery test(is);
    Query q = Query(word);  //用基类指向派生类

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
    while(1)
        test0();

    return 0;
}
