#include <func.h>

int main()
{
    int semArrId=semget(1000,2,IPC_CREAT|0600);
    ERROR_CHECK(semArrId,-1,"semget");
    int ret;
    unsigned short arr[2]={1,1};
    ret=semctl(semArrId,0,SETALL,arr);//设置
    ERROR_CHECK(ret,-1,"semctl");
    memset(arr,0,sizeof(arr));
    ret=semctl(semArrId,0,GETALL,arr);//获取
    ERROR_CHECK(ret,-1,"semctl1");
    printf("arr[0]=%d,arr[1]=%d\n",arr[0],arr[1]);
    return 0;
}

