
#pragma once
#include <iostream>
#include <string> 
#include <string.h>

using namespace std;
#define INF 0
//int dp[1005][1005];     /*dp[i][j]表示表示A串从第0个字符开始到第i个字符和B串从第0个
//                          字符开始到第j个字符，这两个字串的编辑距离。字符串的下标从1开始。*/
/* char a[1005]="word",b[1005] = "wworld";   //a,b字符串从下标1开始 */

//获取一个字节高位为1的个数

namespace ll
{

size_t nByteCode(const char ch);

int lenth(const string str);

int EditDis(string a,string b);
}
