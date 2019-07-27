
#include "DictProducer.h"

using namespace std;


namespace ll
{

DictProducer::DictProducer(Configuration &conf)
: _conf(conf)
{}

void DictProducer::bulid_cn_dict()
{
    map<string,string> mapp = _conf.getConfigMap();
    cout << mapp["yuliao1"] << endl;
    
    ifstream ifs(mapp["yuliaopath"]);
    _splitTool = new CppJieba();
    string str;
    vector<string> cutvec;
    while(getline(ifs,str))
    {
        cout << "1"<<endl;
        cutvec = _splitTool->cut(str);
        for(auto &s : cutvec)
        {
            _dict[s]++;
        }
    }
    ifs.close();
}

void DictProducer::store_dict()
{
    map<string,string> mapp = _conf.getConfigMap();
    ofstream ofs(mapp["dictpath"]);
    for(auto &s : _dict)
    {
        ofs << s.first << ":" << s.second << endl;
    }
}

void DictProducer::bulid_index()
{
    map<string,string> mapp = _conf.getConfigMap();
    ifstream ifs(mapp["dictpath"]);
    string strline;
    while(getline(ifs,strline))
    {
        int idx=0;
        while(strline[idx] != ':')
        {
            idx++; //找到“:"前的词语
        }
        string str(strline.begin(),strline.begin()+idx);
        idx = 0;
        while(strline[idx] != ':')
        {
            int nByte = nByteCode(strline[idx]);
            string sub = strline.substr(idx,nByte); //找到字符
            idx += nByte;
            _index[sub].insert(str);
        }
    }
    ifs.close();
}

void DictProducer::store_index()
{
    map<string,string> mapp = _conf.getConfigMap();
    ofstream ofs(mapp["indexpath"]);
    for(auto &s : _index)
    {
        ofs << s.first << ":";
        auto iter = s.second.begin();
        while(iter != s.second.end())
        {
            ofs << *iter << " ";
            iter++;
        }
        ofs << endl;
    }
    ofs.close();
}

int DictProducer::getCipin(string str)
{
    return _dict[str];
}

map<string,int> &DictProducer::getIdct()
{
    return _dict;
}

}
