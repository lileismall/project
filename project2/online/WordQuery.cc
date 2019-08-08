
#include "WordQuery.h"
#include "jsoncpp/json/json.h"

using namespace std;

namespace ll
{

//通过计算向量的cos@来比较相似度
struct SimilarityCompare
{
    SimilarityCompare(vector<double> & base)
        : _base(base)
    {}

    //通过传入两个向量比较两者与基准向量的相似度
    bool operator()(const pair<int, vector<double> > & lhs, 
                    const pair<int, vector<double> > & rhs)
    {   // 都与基准向量进行计算
        double lhsCrossProduct = 0;
        double rhsCrossProduct = 0;
        double lhsVectorLength = 0;
        double rhsVectorLength = 0;

        for(size_t index = 0; index != _base.size(); ++index)
        {
            lhsCrossProduct += (lhs.second)[index] * _base[index];
            rhsCrossProduct += (rhs.second)[index] * _base[index];
            lhsVectorLength += pow((lhs.second)[index], 2);
            rhsVectorLength += pow((rhs.second)[index], 2);
        }

        if(lhsCrossProduct / sqrt(lhsVectorLength) < rhsCrossProduct / sqrt(rhsVectorLength))
        {   return false;   }
        else
        {   return true;    }
    }

    vector<double> _base; //基准向量
};

WordQuery::WordQuery(Configuration &conf)
    : _conf(conf)
{}

void WordQuery::loadLibrary()
{
    map<string,string> configMap = _conf.getConfigMap();

    //读取网页库和索引库
    ifstream ifsPage(configMap["datapath"]);
    ifstream ifsOffSet(configMap["pdatapath"]);
    if(!ifsOffSet.good() && !ifsPage.good())
    {
        cout << "offset page lib ifstream open error!" << endl;
    }
    int docId,offset,lenth;
    string strline;
    int num = 0;
    while(getline(ifsOffSet,strline))
    {
        stringstream str(strline);
        str >> docId >> offset >> lenth;
        string doc;
        doc.resize(lenth, ' ');
        ifsPage.seekg(offset, ifsPage.beg);
        ifsPage.read(&*doc.begin(), lenth);

        WebPage webPage(doc, _conf, _jieba);
        _pageLib.push_back(webPage);
        _offsetLib.insert(make_pair(docId, make_pair(offset, lenth)));
        /* if(num++ == 5) */
            /* break; */
    }
    ifsOffSet.close();
    ifsPage.close();

    //读取倒排索引库
    ifstream ifsinvert(configMap["invertpath"]);
    if(!ifsinvert.good())
    {
        cout << "ifsinvert open error" << endl;
    }

    double weight;
    string word;
    int cnt = 0;
    while(getline(ifsinvert,strline))
    {
        stringstream str(strline);
        str >> word;
        set<pair<int,double>> IdWight;
        while(str >> docId >> weight)
        {
            IdWight.insert(make_pair(docId,weight));
        }
        _invertIndexTable[word] = IdWight;
        /* if(cnt++ == 5) */
        /*     break; */
    }
    ifsinvert.close();

    /* cout << "------检验库加载是否成功-------" << endl; */
    /* for(auto &s : _invertIndexTable) */
    /* { */
    /*     cout << s.first << endl; */
    /* } */
}

//计算权重，得到基准向量,vector<double>存的就是向量
vector<double> WordQuery::getQueryWordsWeightVector(vector<string> & queryWords) //计算查询词的权重值
{
    //统计词频
    map<string, int> wordFreqMap;
    for(auto item : queryWords)
    {
        ++wordFreqMap[item];
    }

    //计算权重
    vector<double> weightList;
    double weightSum = 0;
    int totalPageNum = _offsetLib.size();

    for(auto & item : queryWords)
    {
        int df = _invertIndexTable[item].size(); //某词语在所有文章出现的次数
        double idf = log(static_cast<double>(totalPageNum) / df + 0.05) / log(2); 
        int tf = wordFreqMap[item];
        double w = idf * tf;
        weightSum += pow(w, 2);
        weightList.push_back(w);
    }

    //归一化
    for(auto & item : weightList)
    {
        item /= sqrt(weightSum);
    }

    cout << "weightList's elem: ";
    for(auto item : weightList)
    {
        cout << __FILE__ << __LINE__ << endl;
        cout << item << "\t";
    }
    cout << endl;

    return weightList;
}

//根据查询词得到别的向量,result存的是多个向量，int->docId,同时含有所有查询词的网页
bool WordQuery::executeQuery(const vector<string> & queryWords,
                             vector<pair<int,vector<double> > > &resultVec)
{
    cout << "executeQuery()" << endl;
    if(queryWords.size() == 0)
    {
        cout <<"empty string not find" << endl;
        return false;
    }   

    typedef set<pair<int, double> >::iterator setIter;
    vector<pair<setIter,int> > iterVec;//保存需要求取交集的迭代器,int用来截至循环的
    //因为是要求必须含有所有查询词，所以先找到木桶的短板，确定含有某一个
    //查询词的最少含有个数
    int minIterNum = 0x7FFFFFFF;
    vector<int> szVec;
    for(auto item : queryWords)
    {
        int sz = _invertIndexTable[item].size(); //sz代表某个查询词在所有文章中的个数
        szVec.push_back(sz);
        if(sz == 0)
            return false;

        if(minIterNum > sz)
            minIterNum = sz;

        iterVec.push_back(make_pair(_invertIndexTable[item].begin(), 0));

    }
    cout << "minIterNum = " << minIterNum << endl;
    bool isExiting = false;
    while(!isExiting)
    {
        size_t idx = 0;
        for(; idx != iterVec.size() - 1; ++idx)
        {
            if((iterVec[idx].first)->first != iterVec[idx+1].first->first)
                break;
        }
        //如果docId都相等
        if(idx == iterVec.size() - 1)
        {   // 找到相同的docid
            vector<double> weightVec;
            int docid = iterVec[0].first->first;//因为docId都相同，所以这里，0，1，2都可以
            //然后将迭代器都后移
            for(idx = 0; idx != iterVec.size(); ++idx)
            {
                weightVec.push_back(iterVec[idx].first->second);
                ++(iterVec[idx].first);//相同时，将每一个迭代器++
                ++(iterVec[idx].second);//同时记录迭代器++的次数
                if(iterVec[idx].second == szVec[idx])
                {   isExiting = true;   }

            }
            resultVec.push_back(make_pair(docid, weightVec));
        }
        //如果docId不是都相同,找到最小的
        else
        {   //找到最小的docid，并将其所在的iter++
            int minDocId = 0x7FFFFFFF;
            int iterIdx;//保存minDocId的迭代器位置
            for(idx = 0; idx != iterVec.size(); ++idx)
            {
                if(iterVec[idx].first->first < minDocId)
                {
                    minDocId = iterVec[idx].first->first;
                    iterIdx = idx;
                }
            }
            ++(iterVec[iterIdx].first);
            ++(iterVec[iterIdx].second);
            if(iterVec[iterIdx].second == szVec[iterIdx])
            {   isExiting = true;   }
        }

    }
    
    /* for(auto &s : resultVec) */
    /* { */
    /*     cout << s.first << " "; */
    /* } */

    return true;
}

string WordQuery::createJson(vector<int> & docIdVec, const vector<string> & queryWords)
{
    Json::Value root;
    Json::Value arr;

    int cnt = 0;
    for(auto id : docIdVec)
    {
        string summary = _pageLib[id].getSummary(queryWords); //获得简要信息
        string url = _pageLib[id].getUrl();
        string title = _pageLib[id].getTitle();

        Json::Value elem;
        elem["title"] = title;
        elem["url"] = url;
        elem["summary"] = summary;
        arr.append(elem);
        if(++cnt == 100)// 最多记录100条
            break;
    }

    root["files"] = arr;
    Json::StyledWriter writer;
    return writer.write(root);
}

string WordQuery::returnNoAnswer()
{
    Json::Value root;
    Json::Value arr;

    Json::Value elem;
    elem["title"] = "no answer";
    elem["summary"] = "no find what you want!";
    arr.append(elem);
    root["files"] = arr;
    Json::StyledWriter writer;
    return writer.write(root);
}

string WordQuery::doQuery(const string & str)
{
    //对输入字符串进行分词
    vector<string> queryWords;
    if(str.size() > 0)
    {
        queryWords = _jieba.cut(str);
    }

    //查询倒排索引库有没有查询词
    for(auto item : queryWords)
    {
        cout << item << '\n';
        auto uit = _invertIndexTable.find(item);
        if(uit == _invertIndexTable.end())
        {
            cout << "can not found " << item << endl;
            //只要有一个查询词不存在，就认为网页不存在
            return returnNoAnswer();
        }
    }
    cout << endl;

    //计算每个词的权重
    vector<double> weightList = getQueryWordsWeightVector(queryWords);
    SimilarityCompare similarityCmp(weightList);

    //执行查询
    vector<pair<int, vector<double> > > resultVec;// int -> docid
    if(executeQuery(queryWords, resultVec))
    {
        stable_sort(resultVec.begin(), resultVec.end(), similarityCmp);
        vector<int> docIdVec;

        for(auto item : resultVec)
        {
            docIdVec.push_back(item.first);
        }
        return createJson(docIdVec, queryWords);

        //将查询结果封装成Json数据
    }
    else
    {
        return returnNoAnswer();
    }
}

}

