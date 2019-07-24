#include <func.h>
#define N 10000000

typedef struct{
    int sum;
    pthread_mutex_t mutex;
}threadInfo_t;
void* threadFunc(void* p)
{
    threadInfo_t *pData=(threadInfo_t*)p;
    int i;
    for(i=0;i<N;i++)
    {
        pthread_mutex_lock(&pData->mutex);
        pData->sum+=1;
        pthread_mutex_unlock(&pData->mutex);
    }
    return NULL;
}
int main()
{
    pthread_t pthid;
    int ret;
    threadInfo_t data;
    data.sum=0;
    ret=pthread_mutex_init(&data.mutex,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
    struct timeval start,end;
    gettimeofday(&start,NULL);
    ret=pthread_create(&pthid,NULL,threadFunc,&data);
    if(ret!=0)
    {
        printf("%s:%s\n","pthread_create",strerror(ret));
        return -1;
    }
    int i;
    for(i=0;i<N;i++)
    {
        pthread_mutex_lock(&data.mutex);
        data.sum+=1;
        pthread_mutex_unlock(&data.mutex);
    }
    pthread_join(pthid,NULL);
    gettimeofday(&end,NULL);
    printf("use time=%ld\n",(end.tv_sec-start.tv_sec)*10000000+end.tv_usec-start.tv_usec);
    printf("I am main thread %d\n",data.sum);
    return 0;
}

