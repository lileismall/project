#include <func.h>

int main()
{
    int shmid;
    shmid=shmget(1000,4096,0600|IPC_CREAT|IPC_EXCL);
    ERROR_CHECK(shmid,-1,"shmget");
    printf("shmid=%d\n",shmid);
    return 0;
}

