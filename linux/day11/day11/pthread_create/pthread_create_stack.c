#include <func.h>
#define N 10000000
void* threadFunc(void* p)
{
    int *sum=(int*)p;
    int i;
    for(i=0;i<N;i++)
    {
        *sum=*sum+1;
    }
    return NULL;
}
int main()
{
    pthread_t pthid;
    int ret;
    int sum=0;
    ret=pthread_create(&pthid,NULL,threadFunc,&sum);
    if(ret!=0)
    {
        printf("%s:%s\n","pthread_create",strerror(ret));
        return -1;
    }
    int i;
    for(i=0;i<N;i++)
    {
        sum=sum+1;
    }
    pthread_join(pthid,NULL);
    printf("I am main thread %d\n",sum);
    return 0;
}

