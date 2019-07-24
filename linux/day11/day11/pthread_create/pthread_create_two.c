#include <func.h>
//创建两个线程
void* threadFunc(void* p)
{
    int *pSum=(int*)p;
    printf("I am child thread,%d\n",*pSum);
    return NULL;
}
int main()
{
    pthread_t pthid1,pthid2;
    int ret;
    int sum=1;
    ret=pthread_create(&pthid1,NULL,threadFunc,&sum);
    if(ret!=0)
    {
        printf("%s:%s\n","pthread_create",strerror(ret));
        return -1;
    }
    sum=2;
    ret=pthread_create(&pthid2,NULL,threadFunc,&sum);
    pthread_join(pthid1,NULL);//只能等待指定线程的退出
    pthread_join(pthid2,NULL);
    printf("I am main thread\n");
    return 0;
}

