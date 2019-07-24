
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <string>

using namespace std;

int main()
{
    /* std::vector<int> range {1,3,3,4}; */
    vector<string> range = {"dga","gfb","agfc"};
    /* string range; */
    /* while(cin >> range) */
    {
        cout << range.back() <<endl;
        do {
            std::copy (std::begin(range), std::end(range), std::ostream_iterator<string>{std::cout, " "});
            std::cout << std::endl;

        }while(std::next_permutation(std::begin(range), std::end(range),[](const string &str1,const string &str2){return str1.back() < str2.back();}));
    }
}

