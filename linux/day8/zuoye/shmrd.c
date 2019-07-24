#include <func.h>

int main(int argc,char* argv[])
{
    int shmid=shmget(2000,4096,0600|IPC_CREAT);
    char buf[1024]={0};
    printf("shmid=%d\n",shmid);
    ERROR_CHECK(shmid,-1,"shmget");
    char *p=(char*)shmat(shmid,NULL,0);
    strcpy(buf,p);
    puts(buf);
    puts(p);
    shmdt(p);
    shmctl(shmid,IPC_RMID,NULL);
    return 0;
}

