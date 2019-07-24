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

//具体类
class Thread
: Noncopyable
{
public:
	using ThreadCallback = function<void()>;

	Thread(ThreadCallback && cb)
	: _pthid(0)
	, _isRunning(false)
	, _cb(std::move(cb))
	{}

	void start();
	void join();

	~Thread();

private:
	static void * threadfunc(void * arg);

private:
	pthread_t _pthid;
	bool _isRunning;
	ThreadCallback _cb;
};

}//end of namespace wd
