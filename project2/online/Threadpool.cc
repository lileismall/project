 ///
 /// @file    Threadpool.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-06 11:32:31
 ///
 
#include "Threadpool.h"
#include "Thread.h"
#include "TimerThread.h"
#include "Configuration.h"

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


void testfunc()
{
    cout << "this is testfunc" <<endl;
}

void Threadpool::start()
{
    //初始化cache
    _cachesManager.initCache(_threadNumber + 1,"cache.txt");  //加1是因为还有一个管理线程
    //创建线程
	for(size_t idx = 1; idx != _threadNumber; ++idx) {
		unique_ptr<Thread> thread(new Thread(
			std::bind(&Threadpool::threadFunc, this),idx  //线程编号和Cache一致
		));
		_threads.push_back(std::move(thread));
	}

	for(auto & thread : _threads) {
		thread->start();
	}

    //创建管理线程
    /* unique_ptr<Thread> managerThread(new Thread( */
    /*          std::bind(&Threadpool::managerFunc,this),0  //0号线程代表管理线程 */
                    /* )); */
    /* managerThread->start(); */
    
    TimerThread *tfd = new TimerThread(1,3,0,std::bind(&Threadpool::managerFunc,this));
    tfd->start();
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

void Threadpool::managerFunc()
{
    /* while(! _isExit) */
    /* { */
        /* sleep(2); */
        _cachesManager.periodicUpdateCaches();
    /* } */
}

LRUCache Threadpool::getCache(size_t num)
{
    return _cachesManager.getCache(num);
}


}//end of namespace ll
