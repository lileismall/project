 ///
 /// @file    Threadpool.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-06 11:28:23
 ///
 
#ifndef __WD_THREADPOOL_H__
#define __WD_THREADPOOL_H__
#include "TaskQueue.h"
#include "Thread.h"
#include "LRUCache.h"

#include <vector>
#include <memory>
#include <functional>
using std::vector;
using std::unique_ptr;

namespace ll
{

//class Thread;
class Threadpool
{
    using Task = std::function<void()>;
public:
	Threadpool(size_t, size_t);

	void start();
	void stop();

	void addTask(Task && task);
    LRUCache getCache(size_t num);

private:
	void threadFunc();
	Task getTask();
    
private:
	size_t _threadNumber; 
	size_t _queSize;
	vector<unique_ptr<Thread>> _threads;
	TaskQueue _que;
	bool _isExit;
    /* vector<LRUCache> _caches; */
    CacheManager _cachesManager;
};

}//end of namespace ll


#endif 
