
#include "pageLib.hpp"
/* #include "judgeEqual.h" */
#include "PageLibPreprocessor.h"
#include "SplitTool.h"
#include <iostream>
#include <sstream>

using namespace std;
using namespace ll;

class ReadLib
{
public:

    ReadLib()
    {
        ifstream ifs("../data/pdata.lib");
        string strline;
        string num,seek,lenth; //网页编号，偏移位置，网页长度
        while(getline(ifs,strline))
        {
            istringstream ss(strline);
            getline(ss,num,'\t');
            getline(ss,seek,'\t');
            getline(ss,lenth,'\t');
            pair<string,string> tt(seek,lenth);
            _indexlib.push_back(tt);
            /* _indexlib[num] = pair<string,string>(seek,lenth); */
        }
    }
    
    void showmap()
    {
        /* for(auto &s : _indexlib) */
        /* { */
            /* cout << s.first << " " << s.second.first */
            /*     << " " << s.second.second << endl; */
        /* } */
        int i=0;
        for(auto &s : _indexlib)
        {
            cout << i++ << " " << s.first << " " << s.second << endl;
        }
    }

    string readLib(int num)  //num代表网页库编号
    {
        ifstream ifs("../data/data.lib");
        char *str = new char[200000];
        int seek = atoi(_indexlib[num].first.c_str());
        int lenth = atoi(_indexlib[num].second.c_str());
        ifs.seekg(seek,ios::beg);
        ifs.read(str,lenth);
        /* cout << *str << endl; */
        /* puts(str); */
        ifs.close();
        return str;
    }

    //返回索引文件的大小
    int getSum()
    {
        return _indexlib.size();
    }
private:
    /* map<string,pair<string,string>> _indexlib; */
    vector<pair<string,string>> _indexlib;  //存索引文件
};



int main()
{

    Configuration conf("../conf/conf");
    CppJieba jieba;
    PageLib pagelib(conf);
    pagelib.create();
        cout << __FILE__ << __LINE__ << endl;
    pagelib.store();
        cout << __FILE__ << __LINE__ << endl;

    PageLibPreprocessor pretest(conf);
    pretest.readInfoFromFile();
    pretest.buildInvertIndexTable();
    pretest.cutRedundantPages();
    pretest.storeOnDisk();

    ReadLib test;
    string dict = test.readLib(0);
    string dict2 = test.readLib(1);
    WebPage web(dict,conf,jieba);
    WebPage web2(dict2,conf,jieba);
    cout << web.getUrl() << endl;
    cout << web2.getUrl() << endl;
    cout << web.getTitle() << endl;
    cout << web.getDocId() << endl;
    cout << web2.getDocId() << endl;
    cout << "两个网页是否相似:" << int(web==web2) << endl;
    cout << "两个网页是否相似:" << int(web==web) << endl;
    

    /* test.showmap(); */
    /* vector<iterator_traits<vector<string>>> itervec; */
    /* for(int i=0;i<sum;i++) */
    /* { */
    /*     dict.push_back(test.readLib(i)); */
    /* } */
    /* SimHarh sh; */
    /* vector<string>::iterator iter1 = dict.begin(); */
    /* while(iter1 != dict.end()) */
    /* { */
    /*     auto iter2 = iter1 + 1; */
    /*     while(iter2 != dict.end()) */
    /*     { */
    /*         if(sh.judgeEqueal(*iter1,*iter2)) */
    /*         { */
    /* cout << __LINE__ << endl; */
    /*             auto tmp = iter2++;  //用来删除 */
    /*             dict.erase(tmp); */
    /*         }else{ */
    /*             iter2++; */
    /*         } */
    /*     } */
    /*     iter1++; */
    /* } */
    
    /* ofstream ofs("../data/data.lib"); */
    /* int te = 0; */
    /* for(auto &s : dict) */
    /* { */
    /*     /1* cout << s << endl; *1/ */
    /*     ofs << s; */
    /*     cout << te++ <<endl; */
    /* } */

    return 0;
}

