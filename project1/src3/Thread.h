 ///
 /// @file    Thread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-07-15 09:40:52
 ///
 
#pragma once

#include "Noncopyable.h"

#include <pthread.h>
#include <functional>
using std::function;
 
namespace ll
{

namespace current_thread
{
#ifndef threadnum
#define threadnum
extern __thread size_t threadNum;
#endif
}

//具体类
class Thread
: Noncopyable
{
public:
	using ThreadCallback = function<void()>;

	Thread(ThreadCallback && cb,size_t tthreadNum)
	: _pthid(0)
	, _isRunning(false)
	, _cb(std::move(cb))
    , _threadNum(tthreadNum)
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
    size_t _threadNum; //线程编号
};

}//end of namespace ll
