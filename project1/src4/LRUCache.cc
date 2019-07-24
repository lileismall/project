#pragma once
#include "LRUCache.h"
#include "nBtyte.h"
#include <istream>
#include <sstream>
/* #include "TimerThread.h" */

using namespace std;


namespace ll
{
void LRUCache::addElement(string s)
{
    auto it = _keys.find(s);//O(1)
    if(it == _keys.end()) {
        if(int(_nodes.size()) == _capacity) {
            //淘汰元素
            string deleteStr = _nodes.back();
            _nodes.pop_back();
            _keys.erase(deleteStr);
        }
        cout << __FILE__ << __LINE__ <<endl;
        _nodes.push_front(s);
        _keys.insert(make_pair(s, _nodes.begin()));
        //_keys[key] = _nodes.begin();
    } else {
        // 更新值
        /* it->second->index= index; */
        _nodes.splice(_nodes.begin(), _nodes, it->second);
        _keys[s] = _nodes.begin();
    }
}

void LRUCache::readFromFile(const string &filename)
{
    ifstream ifs(filename);
    if(!ifs) perror("readFromFile");
    string strline;
    int capacity = 0; //cache大小
    while(capacity < _capacity && getline(ifs,strline))
    {
        istringstream ss(strline);
        vector<string> str;
        string s;
        while(getline(ss,s,' '))
        {
            str.push_back(s);
        }
        size_t i=1;
        while(i < str.size())
        {
            _harhmap[str[0]].insert(str[i]);
            i++;
        }
        capacity++;
    }
    for(auto &s : _harhmap)
    {
        _nodes.push_front(s.first); //初始化队列
    }
    for(auto &s : _nodes)
    {
        _keys[s] = _nodes.begin(); //初始化位置表
    }

    //测试用
    //cout << "this is readFromFile :" <<endl;
    //for(auto &s : _harhmap)
    //{
    //    cout << s.first << ":";
    //    auto iter = s.second.begin();
    //    while(iter != s.second.end())
    //    {
    //        cout << *iter << " ";
    //        iter++;
    //    }
    //    cout << endl;
    //}
}

void LRUCache::writeToFile(const string & filename)
{
    ofstream ofs(filename);
    for(auto &s : _harhmap)
    {
        ofs << s.first << " ";
        for(auto &str : s.second)
        {
            ofs << str << " ";
        }
        ofs << endl;
    }
}

set<string> *LRUCache::tryGet(string s) //尝试在cache中找单词，如果找到返回在字典中位置，如果没找到
{
    auto it = _keys.find(s);
    if(it == _keys.end()) {
        return  NULL;
    } else {
        cout << __FILE__ << __LINE__ <<endl;
        set<string> sstr = _harhmap[s];
        _nodes.splice(_nodes.begin(), _nodes, it->second);
        _keys[s] = _nodes.begin();
        //这里要将在索引中找的的结果加进缓存，_harhmap
        //_harhmap[s] = set<string>;
        return &_harhmap[s];
    }
}

void LRUCache::update(const LRUCache & rhs)  //更新缓存数据
{
    _nodes = rhs._nodes;
    _keys = rhs._keys;
    _harhmap = rhs._harhmap;
}

void LRUCache::showCache()
{
    cout << "this is showCache" <<endl;
    for(auto &s : _harhmap)
    {
        cout << s.first << " ";
    }
    cout << endl;
}


//管理类
void CacheManager::initCache(size_t cacheNum,string filename)
{
    for(size_t i=0; i<cacheNum; i++)
    {
        LRUCache cache;
        cache.readFromFile(filename);
        _cacheVec.push_back(cache);
    }

}

LRUCache &CacheManager::getCache(size_t idx) //获取某个缓存
{
    return _cacheVec[idx];
}

void CacheManager::periodicUpdateCaches()  //定时更新缓存中数据
{      
    for(size_t i=1;i < _cacheVec.size() ;i++)
    {
        _cacheVec[i].update(_cacheVec[0]); //将总的cache附给每个线程的cache
    }
}

}

