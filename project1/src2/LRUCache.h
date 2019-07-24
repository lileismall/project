#pragma once

#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

namespace ll
{
class LRUCache
{
	struct CacheNode
	{
		CacheNode(string s, int indexx)
		: str(s)
        , index(indexx)
		{}
		/* int value; */
        string str; //单词
		int index; //在字典vector中的位置下标
	};
public:
	LRUCache(int capacity = 10)
	: _capacity(capacity)
	{}
	void addElement(string s, int index)
	{
		auto it = _keys.find(s);//O(1)
		if(it == _keys.end()) {
			if(int(_nodes.size()) == _capacity) {
				//淘汰元素
				string deleteStr = _nodes.back().str;
				_nodes.pop_back();
				_keys.erase(deleteStr);
			}
			
			CacheNode node(s,index);
			_nodes.push_front(node);
			_keys.insert(make_pair(s, _nodes.begin()));
			//_keys[key] = _nodes.begin();
		} else {
			// 更新值
			/* it->second->index= index; */
			_nodes.splice(_nodes.begin(), _nodes, it->second);
			_keys[s] = _nodes.begin();
		}
	}

    void readFromFile(const string & filename)  //从文件里读取缓存数据
    {
        ifstream ifs(filename);

    }

    void writeToFile(const string & filename)
    {
        ofstream ofs(filename);
    }

    void update(const LRUCache & rhs);  //更新缓存数据

	int get(string s) //尝试在cache中找单词，如果找到返回在字典中位置，如果没找到，返回-1
	{
		auto it = _keys.find(s);
		if(it == _keys.end()) {
			return -1;
		} else {
			int ret = it->second->index;
			_nodes.splice(_nodes.begin(), _nodes, it->second);
			_keys[s] = _nodes.begin();
			return ret;
		}
	}
	
private:
	int _capacity;  //缓存大小
	list<CacheNode> _nodes; //用以淘汰
	unordered_map<string, list<CacheNode>::iterator> _keys; //记录数据在list中的位置
    unordered_map<string,string> _harhmap; //存放缓存数据
};
 
//int main(void)
//{
//	LRUCache cache(6);
//	cache.addElement("a",2);
//	cout << "get(a) = " << cache.get("a") << endl;
//	cache.addElement("b",3);
//	cout << "get(b) = " << cache.get("b") << endl;
//	//cache.put(4, "c");
//	//cout << "get(1) = " << cache.get(1) << endl;
//	//cout << "get(3) = " << cache.get(3) << endl;
//	//cout << "get(4) = " << cache.get(4) << endl;
//	//cache.put(5, "b");
//	//cout << "get(3) = " << cache.get(3) << endl;
// 
//    return 0;
//}

class CacheManager
{
public:   
    static void initCache(size_t cacheNUm,string filename); //从磁盘文件中读取缓存信息
    static LRUCache getCache(size_t idx); //获取某个缓存
    static void periodicUpdateCaches();  //定时更新缓存中数据,static是因为该函数要作为线程的功能函数

private:
    static vector<LRUCache> _cacheVec;  //缓存数量与线程保持一致,0位置存的是总缓存
};

}
