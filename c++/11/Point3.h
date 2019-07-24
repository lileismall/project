 ///
 /// @file    Point.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-06-18 15:57:18
 ///
 
#pragma once
#include <iostream>
using std::cout;
using std::endl;

class Point
{
public:
	Point()
	: _ix(0)
	, _iy(0)
	{
		cout << "Point()" << endl;
	}

	Point(int ix, int iy)
	: _ix(ix)   
	, _iy(iy)
	{
		cout << "Point(int,int)" << endl;
	}

	void setX(int ix)
	{	_ix = ix;	}


#if 0
	void print(/*     Point * const this    */)
	{
		//非const版本的成员函数是可以修改成员的
		//this = 0x1000;
		_ix = 100;

		cout << "void print()" << endl;
		cout << "(" << this->_ix
			 << "," << this->_iy
			 << ")" << endl;
	}
#endif

	//以后只要某一个函数不会对数据成员进行修改，都要将其设置为
	//const成员函数
#if 1
	void print(/*  const Point * const this    */) const
	{
		//_ix = 100;//error
		cout << "void print() const" << endl;
		cout << "(" << this->_ix
			 << "," << this->_iy
			 << ")" << endl;
	}
#endif

	~Point()
	{
		cout << "~Point()" << endl;
	}

private:
	int _ix;
	int _iy;
};
