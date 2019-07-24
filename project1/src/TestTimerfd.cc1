 ///
 /// @file    TestTimerfd.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-07-19 10:59:37
 ///

#include "TimerThread.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
using std::cout;
using std::endl;

void getNumber()
{
	::srand(::time(nullptr));
	int number = ::rand() % 100;
	cout << ">> sub thread: timerfd  get a number  = " << number << endl;
}
 
int main(void)
{
	ll::TimerThread timer(1, 3, getNumber);
	timer.start();

	cout << "main thread" << endl;
	::sleep(20);
	timer.stop();
 
	return 0;
}
