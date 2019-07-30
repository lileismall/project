
#include <iostream>
#include "simhash/Simhasher.hpp"

using namespace std;
using namespace simhash;

class SimHarh
{
public:
    SimHarh(size_t topN = 5)
    : _topN(topN)
    {
        _simhasher = new Simhasher("simhash/dict/jieba.dict.utf8", "simhash/dict/hmm_model.utf8", "simhash/dict/idf.utf8", "simhash/dict/stop_words.utf8");
    }

    ~SimHarh()
    {
        if(_simhasher)
            delete _simhasher;
    }

    bool judgeEqueal(string l,string r)  //判断两个字符串是否相似
    {
        cout << "正在判断" << endl;
        uint64_t u64_1 = 0,u64_2 = 0;
        _simhasher->make(l, _topN, u64_1);
        _simhasher->make(r, _topN, u64_2);
        return Simhasher::isEqual(u64_1,u64_2);
    }

    u_int64_t computerNum(string str)
    {
        u_int64_t t = 0;
        _simhasher->make(str,_topN,t);
        return t;
    }

    bool judgeEquealNum(u_int64_t l,u_int64_t r) //通过simharh码直接比较
    {
        return Simhasher::isEqual(l,r);
    }
private:
    Simhasher *_simhasher;
    size_t _topN;
};


/* int main() */
/* { */
/*     Simhasher simhasher("../dict/jieba.dict.utf8", "../dict/hmm_model.utf8", "../dict/idf.utf8", "../dict/stop_words.utf8"); */
/*     string s("我是蓝翔技工拖拉机学院多久手扶不用拖拉机专业的。不用多久，我就会升职加薪，当上总经理，出任CEO，走上人生巅峰。"); */
/*     string s2("我是蓝翔技工拖拉机学院手扶拖拉机专。不用多久，我就会升职加薪，当经理，出任CEO，走上人生"); */
/*     size_t topN = 5; */
/*     uint64_t u64_1 = 0,u64_2 = 0; */
/*     vector<pair<string ,double> > res; */
/*     simhasher.extract(s, res, topN); */
/*     simhasher.make(s, topN, u64_1); */
/*     simhasher.make(s2, topN, u64_2); */
/*     for(auto &s : res) */
/*     { */
/*         cout << s.first << ":" << s.second << endl; */
/*     } */
/*     cout << u64_1 << endl; */
/*     cout << u64_2 << endl; */
/*     int re = Simhasher::isEqual(u64_1,u64_2); */
/*     cout << re << endl; */
/*     return 0; */
/* } */

/* int main() */
/* { */
/*     SimHarh test; */
/*     string s("我是蓝翔技工拖拉机学院多久手扶不用拖拉机专业的。不用多久，我就会升职加薪，当上总经理，出任CEO，走上人生巅峰。"); */
/*     string s2("我是蓝翔技工拖拉机学院手扶拖拉机专。不用多久，我就会升职加薪，当经理，出任CEO，走上人生"); */
/*     string a1("我是蓝翔毕业的"); */
/*     string a2("我是蓝翔毕业"); */
/*     bool ret = test.judgeEqueal(a1,a2); */
/*     cout << "两个字符串是否相似:" << ret << endl; */
/* } */
