#include <func.h>

int main()
{
    int shmid;
    shmid=shmget(IPC_PRIVATE,4096,0600|IPC_CREAT);
    ERROR_CHECK(shmid,-1,"shmget");
    printf("shmid=%d\n",shmid);
    return 0;
}

