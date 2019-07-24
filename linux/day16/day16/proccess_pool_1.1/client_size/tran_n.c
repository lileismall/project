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
    }
    return 0;
}

