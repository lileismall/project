
#include "nBtyte.h"

using namespace std;
#define INF 0
//int dp[1005][1005];     /*dp[i][j]表示表示A串从第0个字符开始到第i个字符和B串从第0个
//                          字符开始到第j个字符，这两个字串的编辑距离。字符串的下标从1开始。*/
/* char a[1005]="word",b[1005] = "wworld";   //a,b字符串从下标1开始 */

//获取一个字节高位为1的个数

namespace ll
{


size_t nByteCode(const char ch)
{
    if(ch & (1 << 7))
    {
        int nBytes = 1;
        for(int index = 0;index < 6;index++)
        {
            if(ch & (1 << (6 - index)))
            {
                ++nBytes;
            }else{
                break;
            }
        }
        return nBytes;
    }
    return 1;
}

int lenth(const string str)
{
    int len = 0;
    for(size_t idx = 0;idx < str.size(); idx++)
    {
        int nBytes = nByteCode(str[idx]);
        idx += (nBytes - 1);
        len++;
    }
    return len;
}

int EditDis(string a,string b)
{
    int lena = lenth(a) + 1;
    int lenb = lenth(b) + 1;
    int dp[lena][lenb];
    //初始化
    for(int i=0;i<=lena;i++)
        for(int j=0;j<=lenb;j++)
            dp[i][j] = 0;
    for(int i=1;i<=lena;i++)
        dp[i][0] = i;
    for(int j=1;j<=lenb;j++)
        dp[0][j] = j;
    string suba,subb;
    for(int dist_i = 1,a_idx = 0;dist_i < lena;++dist_i,++a_idx)
    {
        int nBytes = nByteCode(a[a_idx]); //判断字符占用几个字节
        suba = a.substr(a_idx,nBytes);
        /* cout << suba << endl; */
        a_idx += (nBytes - 1);
        for(int dist_j = 1,b_idx = 0;dist_j < lenb;++dist_j,++b_idx)
        {
            nBytes = nByteCode(b[b_idx]);
            subb = b.substr(b_idx,nBytes);
        /* cout << subb << endl; */
            b_idx += (nBytes - 1);
            /* cout << dp[dist_i][dist_j] <<endl; */
            int flag=0;
            if(suba != subb)
            {
                flag = 1;
            }
            dp[dist_i][dist_j] = 
            min(dp[dist_i-1][dist_j]+1,min(dp[dist_i][dist_j-1]+1,dp[dist_i-1][dist_j-1]+flag));
        }
    }
    //for(int i=1;i<=lena;i++)
    //{
    //    for(int j=1;j<=lenb;j++)
    //    {
    //        int flag;
    //        if(a[i]==b[j])
    //            flag=0;
    //        else
    //            flag=1;
    //        dp[i][j]=min(dp[i-1][j]+1,min(dp[i][j-1]+1,dp[i-1][j-1]+flag));
    //        //dp[i-1][j]+1表示删掉字符串a最后一个字符a[i]
    //        //dp[i][j-1]+1表示给字符串添加b最后一个字符
    //        //dp[i-1][j-1]+flag表示改变,相同则不需操作次数,不同则需要,用flag记录
    //    }
    //}
    return dp[lena-1][lenb-1];
}

}

//int main()
//{
//    char a[100] = "王道";
//    char b[100] = "王道";
//    cout <<ll:: EditDis(a,b) <<endl;
//}

