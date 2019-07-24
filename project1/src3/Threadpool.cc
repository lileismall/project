 ///
 /// @file    Threadpool.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-06 11:32:31
 ///
 
#include "Threadpool.h"
#include "Thread.h"

#include <unistd.h>

#include <iostream>
using std::cout;
using std::endl;

namespace ll 
{

Threadpool::Threadpool(size_t threadNumber, size_t queSize)
: _threadNumber(threadNumber)
, _queSize(queSize)
, _que(_queSize) 
, _isExit(false)
{
	_threads.reserve(_threadNumber);
}


void Threadpool::start()
{
	for(size_t idx = 0; idx != _threadNumber; ++idx) {
		unique_ptr<Thread> thread(new Thread(
			std::bind(&Threadpool::threadFunc, this),idx+1
		));
		_threads.push_back(std::move(thread));
	}

	for(auto & thread : _threads) {
		thread->start();
	}
}

void Threadpool::stop()
{
	if(!_isExit) {
		//先将任务队列中的任务执行完毕
		while(!_que.empty()) {
			::sleep(1);
		}

		_isExit = true;
		cout << ">>> _isExit = true " << endl;

		_que.wakeup();

		for(auto & thread : _threads) {
			thread->join();
		}
	}
}

void Threadpool::addTask(Task && task)
{
	_que.push(task);
}

Task Threadpool::getTask()
{
	return _que.pop();
}

//每一个子线程运行
void Threadpool::threadFunc()
{
	while(!_isExit) {  //为什么可以用，因为这里将this的指针也一起传给子线程了
		Task task = getTask();
		if(task) {
			task();
		}
	}
}


}//end of namespace ll
