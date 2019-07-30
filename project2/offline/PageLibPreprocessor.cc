
#include "PageLibPreprocessor.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
/* #include "judgeEqual.h" */
#include <queue>
using namespace std;

namespace ll
{

WebPage::WebPage(string &doc,
                 Configuration &config,CppJieba &jieba)
    : _doc(doc)
{
    processDoc(doc,config,jieba);
}

void WebPage::processDoc(const string &doc,
                         Configuration &config,CppJieba &jieba)
{
    string docIdHead = "<docid>";
    string docIdTail = "</docid>";
    string docUrlHead = "<url>";
    string docUrlTail = "</url>";
    string docTitleHead = "<title>";
    string docTitleTail = "</title>";
    string docContentHead = "<content>";
    string docContentTail = "</content>";
    //提取docId
    int bpos = doc.find(docIdHead);  //找到出现该字符串位置
    int epos = doc.find(docIdTail);
    string docId = doc.substr(bpos + docIdHead.size(), 
                               epos - bpos - docIdHead.size());
    /* cout << atoi(docId.c_str()) << endl; */
    _docId = atoi(docId.c_str());
    //url
    bpos = doc.find(docUrlHead);
    epos = doc.find(docUrlTail);
    _docUrl = doc.substr(bpos + docUrlHead.size(),
                         epos - bpos - docTitleHead.size() + 2); //不知道为什么会少读两个字符
    //title
    bpos = doc.find(docTitleHead);
    epos = doc.find(docTitleTail);
    _docTitle = doc.substr(bpos + docTitleHead.size(), 
                           epos - bpos - docTitleHead.size());

    //content
    bpos = doc.find(docContentHead);
    epos = doc.find(docContentTail);
    _docContent = doc.substr(bpos + docContentHead.size(),
                             epos - bpos - docContentHead.size());

    vector<string> wordsVec = jieba.cut(_docContent.c_str());
    set<string> & stopWordList = config.getStopWordList();
    calcTopK(wordsVec,stopWordList);
}

//优先级队列要使用的比较函数对象
struct WordFreqCompare
{
    bool operator()(const pair<string, int> & left, const pair<string, int> & right)
    {
        if(left.second < right.second)
        {   return true;    }
        else if(left.second == right.second && left.first > right.first)
        {   return true;    }
        else
        {   return false;   }
    }

};

void WebPage::calcTopK(vector<string> &wordsVec,set<string> &stopWordList)
{
    //统计词频
    for(auto iter = wordsVec.begin(); iter != wordsVec.end(); ++iter)
    {
        //判断是否是停用词
        auto sit = stopWordList.find(*iter);
        if(sit == stopWordList.end())
        {
            ++_wordsMap[*iter];
        }
    }

    priority_queue<pair<string,int>,vector<pair<string,int>>,
        WordFreqCompare> wordFreQue(_wordsMap.begin(),_wordsMap.end());
    while(!wordFreQue.empty())
    {
        string top = wordFreQue.top().first;
        wordFreQue.pop();
        _topWords.push_back(top);
        if(_topWords.size() > TOPK_NUMBER)
        {
            break;
        }
    }
#if 0
    cout << "------------20个关键字-----------" << endl;
    for(auto &s : _topWords)
    {
        cout << s << endl;
    }
#endif
}

//判断两个网页是否相似,通过比较关键词的相关性
bool operator == (const WebPage & lhs, const WebPage & rhs) 
{
    int commNum = 0;
    auto lIter = lhs._topWords.begin();
    for(;lIter != lhs._topWords.end(); ++lIter)
    {
        commNum += std::count(rhs._topWords.begin(), rhs._topWords.end(), *lIter);

    }

    int lhsNum = lhs._topWords.size();
    int rhsNum = rhs._topWords.size();
    int totalNum = lhsNum < rhsNum ? lhsNum : rhsNum;

    if( static_cast<double>(commNum) / totalNum > 0.75  )
    {   return true;    }
    else 
    {   return false;   }

}

//按照docId进行比较大小
bool operator < (const WebPage & lhs, const WebPage & rhs)
{
    if(lhs._docId < rhs._docId)
        return true;
    else 
        return false;

}

void PageLibPreprocessor::doProcess()
{
    readInfoFromFile();
    time_t t1 = time(NULL);
    cutRedundantPages();
    buildInvertIndexTable();
    time_t t2 = time(NULL);
    printf("preprocess time: %ld s\n", (t2 - t1));

    storeOnDisk();
    time_t t3 = time(NULL);
    printf("store time: %ld min", (t3 - t2));

}

void PageLibPreprocessor::readInfoFromFile()
{
    map<string,string> &configMap = _conf.getConfigMap();
    string pageLibPath = configMap["datapath"];
    if(!pageLibPath.size()) cout << "datapath error" << __FILE__ << endl;
    string offsetLibPath = configMap["pdatapath"];
    if(!pageLibPath.size()) cout << "pdatapath error" << __FILE__ << endl;

    ifstream pageIfs(pageLibPath.c_str());
    ifstream offsetIfs(offsetLibPath.c_str());

    if((!pageIfs.good()) || (!offsetIfs.good()))
    {
        cout << "page or offset lib open error" << endl;
    }

    string line;
    int docId, docOffset, docLen;
    string sdocId, sdocOffset, sdocLen;

    while(getline(offsetIfs, line))
    {
        stringstream ss(line);
        ss >> sdocId >> sdocOffset >> sdocLen;
        //字符串转为数字
        docId = atoi(sdocId.c_str());
        docOffset = atoi(sdocOffset.c_str());
        docLen = atoi(sdocLen.c_str());

        string doc;
        doc.resize(docLen, ' ');
        pageIfs.seekg(docOffset, pageIfs.beg);
        pageIfs.read(&*doc.begin(), docLen);

        /* cout <<__FILE__<<__LINE__ << doc << endl; */
        WebPage webPage(doc, _conf, _jieba);
        _pageLib.push_back(webPage);

        _offsetLib.insert(std::make_pair(docId, std::make_pair(docOffset, docLen)));
    }
#if 0
    for(auto mit : _offsetLib)
    {
        cout << mit.first << "\t" << mit.second.first << "\t" << mit.second.second << endl;

    }
#endif

}

//去重
void PageLibPreprocessor::cutRedundantPages()
{
    for(size_t i = 0; i < _pageLib.size(); ++i)
    {
        for(size_t j = i + 1; j < _pageLib.size(); ++j)
        {
            if(_pageLib[i] == _pageLib[j])
            {
                _pageLib[j] = _pageLib[_pageLib.size() - 1];
                _pageLib.pop_back();
                --j;
            }
        }
    }
}

void PageLibPreprocessor::buildInvertIndexTable()
{
    for(auto &page : _pageLib)
    {
        map<string,int>& wordsMap = page.getWordsMap();
        for(auto &wordFreq : wordsMap)
        {
            //先将docId加入,权重先置为0
            pair<int,double> tt(page.getDocId(),wordFreq.second);
            _invertIndexTable[wordFreq.first].push_back((tt)); 
        }

    }

    //计算每篇文档中的词的权重,并归一化
    /* map<int, double> weightSum;// 保存每一篇文档中所有词的权重平方和. int 代表docid */
    long weightSum=0;

    int totalPageNum = _pageLib.size();
    for(auto & item : _invertIndexTable)
    {   
        int df = item.second.size();
        //求关键词item.first的逆文档频率
        double idf = log(static_cast<double>(totalPageNum)/ df + 0.05) / log(2);

        for(auto & sitem : item.second)
        {
            double weight = sitem.second * idf;

            /* weightSum[sitem.first] += pow(weight, 2); */
            weightSum += pow(weight, 2);  //平方和
            sitem.second = weight;
        }
    }

    for(auto & item : _invertIndexTable)
    {   //归一化处理
        for(auto & sitem : item.second)
        {
            sitem.second = sitem.second / sqrt(weightSum);
        }
    }


#if 0 // for debug
    for(auto item : _invertIndexTable)
    {
        cout << item.first << "\t";
        for(auto sitem : item.second)
        {
            cout << sitem.first << "\t" << sitem.second <<  "\t";
        }
        cout << endl;
    }
#endif
}

//将去重后的库存入文件
void PageLibPreprocessor::storeOnDisk()
{
    sort(_pageLib.begin(), _pageLib.end()); 
    ofstream ofsPageLib(_conf.getConfigMap()["datapath"].c_str()); //网页库流
    ofstream ofsOffsetLib(_conf.getConfigMap()["pdatapath"].c_str()); //索引库流
    if( !ofsPageLib.good() || !ofsOffsetLib.good() )
    {   
        cout << "new page or offset lib ofstream open error!" << endl;
    }

    for(auto & page : _pageLib)
    {
        int id = page.getDocId();
        int length = page.getDoc().size();
        ofstream::pos_type offset = ofsPageLib.tellp();
        ofsPageLib << page.getDoc();
        ofsOffsetLib << id << '\t' << offset << '\t' << length << '\n';
    }

    ofsPageLib.close();
    ofsOffsetLib.close();

    // invertIndexTable
    ofstream ofsInvertIndexTable(_conf.getConfigMap()["invertpath"].c_str());
    if(!ofsInvertIndexTable.good())
    {
        cout << "invert index table ofstream open error!" << endl;
    }
    for(auto item : _invertIndexTable)
    {
        ofsInvertIndexTable << item.first << "\t";
        for(auto sitem : item.second)
        {
            ofsInvertIndexTable << sitem.first << "\t" << sitem.second <<  "\t";
        }
        ofsInvertIndexTable << endl;
    }
    ofsInvertIndexTable.close();
}

}//end of namespace ll
