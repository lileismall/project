 ///
 /// @file    Condition.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-06-24 11:19:32
 ///
 
#pragma once

#include "MutexLock.h"

#include <iostream>
using std::cout;
using std::endl;
 
namespace ll
{

class Condition
{
public:
	Condition(MutexLock & mutex)
	: _mutex(mutex)
	{
		if(pthread_cond_init(&_cond, nullptr)) {
			perror(">> pthread_cond_init");
		}
	}

	void wait()
	{
		if(pthread_cond_wait(&_cond, _mutex.getMutexLockPtr())) {
			perror(">> pthread_cond_wait");
		}
	}

	void notify()
	{
		if(pthread_cond_signal(&_cond)) {
			perror(">> pthread_cond_signal");
		}
	}

	void notifyAll()
	{
		if(pthread_cond_broadcast(&_cond)) {
			perror(">> pthread_cond_broadcast");
		}
	}

	~Condition()
	{
		if(pthread_cond_destroy(&_cond)) {
			perror(">> pthread_cond_destroy");
		}
	}

private:
	pthread_cond_t _cond;
	MutexLock & _mutex;
};


}//end of namespace wd
