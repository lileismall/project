 ///
 /// @file    Thread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-07-15 09:43:12
 ///

#include "Thread.h"

#include <iostream>
using std::cout;
using std::endl;


namespace ll
{

__thread size_t current_thread::threadNum = 0;

struct ThreadData
{
    using ThreadCallback = function<void()>;

    ThreadData(size_t num,ThreadCallback &&cb)
    : _num(num)
    , _cb(std::move(cb))
    {}

    ~ThreadData() 
    {
    }

    void runInThread()
    {
        current_thread::threadNum = _num;
        if(_cb)
            _cb();
    }

    size_t _num;
    ThreadCallback _cb;
};

void Thread::start()
{
    ThreadData *threadData = new ThreadData(_threadNum,std::move(_cb));
	pthread_create(&_pthid, nullptr, threadfunc, threadData);	
	_isRunning = true;
}

void * Thread::threadfunc(void * arg)
{
	ThreadData* threadData = static_cast<ThreadData*>(arg);
	if(threadData)
		threadData->runInThread();	

	return nullptr;
}

void Thread::join()
{
	if(_isRunning)
		pthread_join(_pthid, nullptr);
}

Thread::~Thread()
{
	if(_isRunning) 
		pthread_detach(_pthid);
}

}//end of namespace ll
