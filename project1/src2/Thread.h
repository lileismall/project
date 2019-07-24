 ///
 /// @file    Thread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-07-15 09:40:52
 ///
 
#pragma once

#include "Noncopyable.h"
#include "LRUCache.h"

#include <pthread.h>
#include <functional>
using std::function;
 
namespace ll
{

__thread size_t threadNUm = 0;

//具体类
class Thread
: Noncopyable
{
public:
	using ThreadCallback = function<void()>;

	Thread(ThreadCallback && cb,size_t threadNum)
	: _pthid(0)
	, _isRunning(false)
	, _cb(std::move(cb))
    , _threadNum(threadNum)
	{}

	void start();
	void join();

	~Thread();

private:
	static void * threadfunc(void * arg);  //用static是避免this指针

private:
	pthread_t _pthid;
	bool _isRunning;
	ThreadCallback _cb;
    size_t _threadNum;
};

}//end of namespace ll
