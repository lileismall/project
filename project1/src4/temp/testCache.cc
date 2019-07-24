
#include <iostream>
#include "LRUCache.h"

using namespace std;
using namespace ll;

int main()
{

    /* LRUCache cache; */
    /* cache.readFromFile("cache.txt"); */
    /* cache.writeToFile("write.txt"); */

    CacheManager test;
    test.initCache(4,"cache.txt");
    LRUCache cache = test.getCache(0);
    cache.showCache();
#if 1
    string ss;
    while(cin >> ss)
    {
        auto s = cache.tryGet(ss);
        if(s)
        {
            for(auto &str : *s)
            {
                cout << str << " ";
            }
            cout << endl;
        }
    }
    /* CacheManager test; */
    /*SXZXZXtest.initCache(4,"cache.txt"); */
#endif
    return 0;
}

