
#include "query.h"

int main()
{   
    ifstream os("file");
    TextQuery test(os);
    print(cout,test.query("are"));
    
    return 0;
}

