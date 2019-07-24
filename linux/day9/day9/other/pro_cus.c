#include <func.h>

int main()
{
    int semArrId=semget(1000,2,IPC_CREAT|0600);
    ERROR_CHECK(semArrId,-1,"semget");
    int ret;
    unsigned short arr[2]={10,0};//第一个信号量代表仓库个数，第二个代表产品个数
    ret=semctl(semArrId,0,SETALL,arr);//设置
    ERROR_CHECK(ret,-1,"semctl");
    if(!fork())//子进程是消费者，出库
    {
        struct sembuf sopp,sopv;
        sopp.sem_num=1;
        sopp.sem_op=-1;
        sopp.sem_flg=0;
        sopv.sem_num=0;
        sopv.sem_op=1;
        sopv.sem_flg=0;
        while(1)
        {
            printf("I am customer,space=%d,productor=%d\n",semctl(semArrId,0,GETVAL),semctl(semArrId,1,GETVAL));
            semop(semArrId,&sopp,1);
            printf("I am customer start consuming\n");
            semop(semArrId,&sopv,1);
            printf("I am customer,space=%d,productor=%d\n",semctl(semArrId,0,GETVAL),semctl(semArrId,1,GETVAL));
            sleep(2);
        }

    }else{//父进程是生产者，入库
        struct sembuf sopp,sopv;
        sopp.sem_num=0;
        sopp.sem_op=-1;
        sopp.sem_flg=0;
        sopv.sem_num=1;
        sopv.sem_op=1;
        sopv.sem_flg=0;
        while(1)
        {
            printf("I am producer,space=%d,productor=%d\n",semctl(semArrId,0,GETVAL),semctl(semArrId,1,GETVAL));
            semop(semArrId,&sopp,1);
            printf("I am producer start producing\n");
            semop(semArrId,&sopv,1);
            printf("I am producer,space=%d,productor=%d\n",semctl(semArrId,0,GETVAL),semctl(semArrId,1,GETVAL));
            sleep(1);
        }
    }
    return 0;
}

