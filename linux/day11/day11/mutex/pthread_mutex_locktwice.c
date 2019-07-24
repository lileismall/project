#include <func.h>
#define N 10000000

typedef struct{
    int sum;
    pthread_mutex_t mutex;
}threadInfo_t;
void* threadFunc(void* p)
{
    threadInfo_t *pData=(threadInfo_t*)p;
    pthread_mutex_lock(&pData->mutex);
    int ret=pthread_mutex_lock(&pData->mutex);
    printf("ret=%d\n",ret);
    pthread_exit(NULL);
}
int main()
{
    pthread_t pthid;
    int ret;
    threadInfo_t data;
    data.sum=0;
    pthread_mutexattr_t mutexAttr;
    pthread_mutexattr_init(&mutexAttr);
    pthread_mutexattr_settype(&mutexAttr,PTHREAD_MUTEX_ERRORCHECK);
    ret=pthread_mutex_init(&data.mutex,&mutexAttr);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
    ret=pthread_create(&pthid,NULL,threadFunc,&data);
    if(ret!=0)
    {
        printf("%s:%s\n","pthread_create",strerror(ret));
        return -1;
    }
    pthread_join(pthid,NULL);
    printf("I am main thread\n"); 
    return 0;
}

