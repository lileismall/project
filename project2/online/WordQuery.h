#pragma once
#include "PageLibPreprocessor.h"


namespace ll
{

class WordQuery
{
public:
    WordQuery(Configuration &conf);
    ~WordQuery() {}

    string doQuery(const string & str);  //执行查询，返回结果
    void loadLibrary();  //加载库文件
    vector<double> getQueryWordsWeightVector(
                     vector<string> & queryWords); //计算查询词的权重值
    bool executeQuery(  const vector<string> & queryWords,
                      vector<pair<int,vector<double> > > &resultVec);  //执行查询
    string createJson(vector<int> & docIdVec,
                      const vector<string> & queryWords); 
    string returnNoAnswer(); 

private:
    Configuration &_conf;
    CppJieba _jieba;
    vector<WebPage> _pageLib;
    unordered_map<int, pair<int, int> >  _offsetLib;    // 网页偏移库对象
    unordered_map<string, set<pair<int, double>>> _invertIndexTable;   // 倒排索引表对象
};

}
