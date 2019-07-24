#include <func.h>

int recvCycle(int sfd,void* pStart,int recvLen)
{
    char *p=(char*)pStart;
    int total=0;
    int ret;
    while(total<recvLen)
    {
        ret=recv(sfd,p+total,recvLen-total,0);
        total=total+ret;
        printf("%5.2f%%\r",(double)total/recvLen*100);
        fflush(stdout);
    }
    printf("\n");
    return 0;
}

