#include <func.h>

int main()
{
    int semArrId=semget(1000,1,IPC_CREAT|0600);
    ERROR_CHECK(semArrId,-1,"semget");
    int ret;
    ret=semctl(semArrId,0,SETVAL,5);
    ERROR_CHECK(ret,-1,"semctl");
    ret=semctl(semArrId,0,GETVAL);
    printf("semval=%d\n",ret);
    return 0;
}

