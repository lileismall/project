#include <func.h>

int g_iSeq=0;
void SignHandler(int iSignNo)
{
    int iSeq=g_iSeq++;
    printf("%d Enter SignHandler,signo:%d\n",iSeq,iSignNo);
    sleep(3);
    printf("%d Leave SignHandler,signo:%d\n",iSeq,iSignNo);
}
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

//struct sigaction {
//    void       (*sa_handler)(int); //信号处理程序，不接受额外数据，SIG_IGN 为忽略，SIG_DFL 为默认动作
//    void       (*sa_sigaction)(int, siginfo_t *, void *); //信号处理程序，能够接受额外数据和sigqueue配合使用
//    sigset_t   sa_mask;//阻塞关键字的信号集，可以再调用捕捉函数之前，把信号添加到信号阻塞字，信号捕捉函数返回之前恢复为原先的值。
//    int        sa_flags;//影响信号的行为SA_SIGINFO表示能够接受数据
//
//};
//回调函数句柄sa_handler、sa_sigaction只能任选其一
int main()
{
    char szBuf[8];
    int iRet;
    signal(SIGINT,SignHandler);
    signal(SIGQUIT,SignHandler);
    do{
        iRet=read(STDIN_FILENO,szBuf,sizeof(szBuf)-1);
        if(iRet<0){
            perror("read fail.");
            break;

        }
        szBuf[iRet]=0;
        printf("Get: %s",szBuf);

    }while(strcmp(szBuf,"quit\n")!=0);
    return 0;

}

