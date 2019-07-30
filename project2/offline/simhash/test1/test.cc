
#include <iostream>
#include "../Simhasher.hpp"

using namespace std;
using namespace simhash;

int main()
{
    Simhasher simhasher("../dict/jieba.dict.utf8", "../dict/hmm_model.utf8", "../dict/idf.utf8", "../dict/stop_words.utf8");
    string s("我是蓝翔技工拖拉机学院多久手扶不用拖拉机专业的。不用多久，我就会升职加薪，当上总经理，出任CEO，走上人生巅峰。");
    string s2("我是蓝翔技工拖拉机学院手扶拖拉机专。不用多久，我就会升职加薪，当经理，出任CEO，走上人生");
    size_t topN = 5;
    uint64_t u64_1 = 0,u64_2 = 0;
    vector<pair<string ,double> > res;
    simhasher.extract(s, res, topN);
    simhasher.make(s, topN, u64_1);
    simhasher.make(s2, topN, u64_2);

    for(auto &s : res)
    {
        cout << s.first << ":" << s.second << endl;
    }

    cout << u64_1 << endl;
    cout << u64_2 << endl;
    int re = Simhasher::isEqual(u64_1,u64_2);
    cout << re << endl;
    return 0;
}

