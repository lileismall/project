#include "process_poll.h"

int recvCycle(int sfd,void *pstrat,int recvLen)
{
    char* p=(char*)pstrat;
    int total=0,ret;
    while(total<recvLen)
    {
        ret=recv(sfd,p+total,recvLen,0);
        total += ret;
    }
    return 0;
}
