#pragma once

#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <set>
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

	void addElement(string s);

    void readFromFile(const string & filename);  //从文件里读取缓存数据

    void writeToFile(const string & filename);

    void update(const LRUCache & rhs);  //更新缓存数据

	set<string> *tryGet(string s); //尝试在cache中找单词，如果找到返回在字典中位置，如果没找到

    //用来测试
    void showCache();
	
private:
	int _capacity;  //缓存大小
	list<string> _nodes; //用以淘汰
	unordered_map<string, list<string>::iterator> _keys; //记录数据在list中的位置
    unordered_map<string,set<string>> _harhmap; //存放缓存数据
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
    void initCache(size_t cacheNUm,string filename); //从磁盘文件中读取缓存信息
    LRUCache &getCache(size_t idx); //获取某个缓存
    void periodicUpdateCaches();  //定时更新缓存中数据,static是因为该函数要作为线程的功能函数

private:
    vector<LRUCache> _cacheVec;  //缓存数量与线程保持一致,0位置存的是总缓存
};

}
