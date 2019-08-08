 ///
 /// @file    TimerThread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-07-19 11:15:43
 ///
 
#pragma once
#include "Thread.h"
#include "Timerfd.h"
#include <iostream>
using std::cout;
using std::endl;
 
namespace ll
{

class TimerThread
{
	using TimerCallback = function<void()>;
public:
	TimerThread(int initialTime, int intervalTime,int thnum, TimerCallback && cb)
	: _timer(initialTime, intervalTime, std::move(cb))
	, _thread(std::bind(&Timerfd::start, &_timer),thnum)
	{
	}

	void start()
	{
		_thread.start(); 
	}

	void stop()
	{
		_timer.stop();
		_thread.join();
	}

private:
	Timerfd _timer;
	Thread _thread;
};

}//end of namespace ll
