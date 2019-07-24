
/* #include "SplitTool.h" */
#include "Configuration.h"
#include "DictProducer.h"

#include <iostream>
#include <map>
#include <string>
#include <set>
#include <fstream>

using namespace std;
using namespace cppjieba;
using namespace ll;

void test()
{
    Configuration conf("../conf/conf");
    CppJieba test;
    test.cut("你是一个小狗");
}

void test1()
{
    map<string,int> test;
    test["a"] = 1;
    test["a"] = 2;

    for(auto &s : test)
    {
        cout << s << endl;
    }
    
}

void test2()
{
    map<string,set<int>> test;
    set<int> set1;
    set1.insert(2);
    test.insert(make_pair("a",set1));
    test.begin()->second.insert(3);
    test["a"].insert(4);
    for(auto &s : test)
    {
        cout << s.second << endl;
    }
}

void test3()
{
    ofstream ofs("file");
    ofs << "test1" << ":" << 3 << endl;
    ofs << "test1" << ":" << 3 << endl;
    ofs.close();
}
    
void test4()
{
    Configuration conf("../conf/conf");   
    DictProducer test(conf);
    /* test.bulid_cn_dict(); */
    /* test.store_dict(); */
    test.bulid_index();
    /* test.store_index(); */
    string str;
    cin >> str;
    vector<string> singstr;
    string s;
    int i=0;
    //将词语中的字符提取出来
    while(str[i])
    {
        int nBytes = nByteCode(str[i]);
        s = str.substr(i,nBytes);
        singstr.push_back(s);
        i += nBytes;
    }
    map<string,set<string>> mapp = test.getindex();
    for(size_t i=0;i<singstr.size();i++)
    {
        auto s = mapp[singstr[i]];
    /* } */
    /* for(auto &s : mapp) */
    /* { */
        for(auto &ss : s)
        {
            cout << ss << "-->" << str
            << " : "<< EditDis(ss,str) << endl ;
        }
    }
}

int main()
{
    test4();
}
