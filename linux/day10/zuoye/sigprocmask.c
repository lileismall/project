#include <func.h>

int main(int argc,char* argv[])
{
   sigset_t sigset;
   sigemptyset(&sigset);
   sigaddset(&sigset,SIGINT);
   sigprocmask(SIG_BLOCK,&sigset,NULL);
   sleep(3);
   sigset_t pend;
   sigpending(&pend);
   if(sigismember(&pend,SIGINT))
   {
       printf("%d is pending\n",SIGINT);
   }else{
       printf("%d is not pending\n",SIGINT);
   }
   sigprocmask(SIG_UNBLOCK,&sigset,NULL);
   while(1);
   return 0;
}

