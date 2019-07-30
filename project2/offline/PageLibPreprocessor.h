#pragma once
#include "Configuration.hpp"
#include "SplitTool.h"
#include <unordered_map>
/* #include <bits/std_function.h> */
#include <set>

using namespace ll;

namespace ll
{

class WebPage
{
    friend bool operator==(const WebPage & lhs,
                           const WebPage & rhs);  //判断两篇文档是否相等
        friend bool operator < (const WebPage & lhs,
                                const WebPage & rhs); //对文档按Docid进行排序
public:
    WebPage(string & doc,
            Configuration & config,
            CppJieba & jieba); // 构造函数
    int getDocId() { return _docId;  }  //获取文档的docid
    string getTitle() {return _docTitle;}
    string getDoc() {return _doc;} //获取文档
    string getUrl() {return _docUrl;}
    map<string, int> & getWordsMap() {return _wordsMap;}    //获取文档的词频统计map
    void processDoc(const string & doc,
                    Configuration & config,
                    CppJieba& jieba);  //对格式化文档进行处理
    void calcTopK(vector<string> & wordsVec,
                  set<string> & stopWordList);   //求取文档的topk词集
public:
    const static int TOPK_NUMBER = 20;  
    string _doc;    //整篇文档，包含xml在内
    int  _docId; //文档id
    string _docTitle;   //文档标题
    string _docUrl; //文档URL
    string _docContent; //文档内容
    string _docSummary; //文档摘要，需自动生成，不是固定的
    vector<string> _topWords;  //词频最高的前20个词
    map<string,int> _wordsMap;  //保存每篇文档的所有词语和词频，不包括停用词
};

class PageLibPreprocessor
{
public:
    PageLibPreprocessor(Configuration &conf)
    : _conf(conf)
    {}
    ~PageLibPreprocessor() {}

    void doProcess();    //执行预处理
/* private: */
    void readInfoFromFile(); //根据配置信息读取网页库和位置偏移库的内容
    void cutRedundantPages();    //对冗余的网页进行去重
    void buildInvertIndexTable();   // 创建倒排索引表
    void storeOnDisk();  //将经过预处理之后的网页库、位置偏移库和倒排索引表写回到磁盘上

private:
    vector<WebPage> _pageLib;  // 网页库的容器对象
    CppJieba _jieba;
    unordered_map<int, pair<int, int> >  _offsetLib;    // 网页偏移库对象
    unordered_map<string, vector<pair<int, double>>> _invertIndexTable;   // 倒排索引表对象
    Configuration &_conf;
};

}
