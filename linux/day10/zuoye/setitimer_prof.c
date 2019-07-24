#include <func.h>
void Handler(int signum)
{
    time_t now=time(NULL);
    printf("%s\n",ctime(&now));   //记住这里要有取地址符
}
int main(int argc,char* argv[])
{
   signal(SIGPROF,Handler);  //真是计时器发的是SIGALRM信号
   Handler(0);
   struct itimerval tt;
   bzero(&tt,sizeof(tt));
   tt.it_value.tv_sec=3;
   tt.it_interval.tv_sec=2;
   int ret=setitimer(ITIMER_PROF,&tt,NULL);
   ERROR_CHECK(ret,-1,"setitimer");
   while(1);
}

