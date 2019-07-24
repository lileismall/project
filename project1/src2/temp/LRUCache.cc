
#include "LRUCache.h"
/* #include "TimerThread.h" */

using namespace std;

namespace ll
{

void CacheManager::initCache(size_t cacheNum,string filename)
{
    for(size_t i=0; i<cacheNum; i++)
    {
        LRUCache cache;
        cache.readFromFile(filename);
        _cacheVec.push_back(cache);
    }

}

LRUCache CacheManager::getCache(size_t idx) //获取某个缓存
{
    return _cacheVec[idx];
}

void CacheManager::periodicUpdateCaches()  //定时更新缓存中数据
{      
    for(size_t i=1;i < _cacheVec.size() ;i++)
    {
        _cacheVec[i].update(_cacheVec[0]);
    }
}



