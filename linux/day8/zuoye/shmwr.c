#include <func.h>

int main(int argc,char* argv[])
{
    int shmid=shmget(2000,4096,0600|IPC_CREAT);
    printf("shmid=%d\n",shmid);
    ERROR_CHECK(shmid,-1,"shmget");
    char *p=(char*)shmat(shmid,NULL,0);
    memset(p,0,4096);
    strcpy(p,"how are you");
    shmdt(p);
    return 0;
}

