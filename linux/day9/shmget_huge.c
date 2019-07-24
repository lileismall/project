#include <func.h>
#define HUGE_2MB 1<<21
int main(int argc,char* argv[])
{
    int shmid=shmget(2000,HUGE_2MB,0600|IPC_CREAT|SHM_HUGETLB);
    ERROR_CHECK(shmid,-1,"shmget");
    printf("shmid=%d\n",shmid);
    return 0;
}

