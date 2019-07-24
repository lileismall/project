
#include <iostream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
    vector<string> s;
    ostream_iterator<string> os(cout," ");
    istream_iterator<string> is(cin);
    /* cout << accumulate(is,of,0) << endl; */
    /* copy(is,istream_iterator<string>(),back_inserter(s)); */
    copy(is,istream_iterator<string>(),os);
    /* cout << *is << endl; */
    //for(auto &ss : s)
    //{
    //    cout << ss << endl;
    //}

    return 0;
}

