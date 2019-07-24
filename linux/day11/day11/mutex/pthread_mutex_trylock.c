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
    pthread_mutex_unlock(&pData->mutex);
    pthread_exit(NULL);
}
int main()
{
    pthread_t pthid;
    int ret;
    threadInfo_t data;
    data.sum=0;
    ret=pthread_mutex_init(&data.mutex,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
    ret=pthread_create(&pthid,NULL,threadFunc,&data);
    if(ret!=0)
    {
        printf("%s:%s\n","pthread_create",strerror(ret));
        return -1;
    }
    pthread_join(pthid,NULL);
    ret=pthread_mutex_trylock(&data.mutex);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_trylock");
    printf("I am main thread\n"); 
    pthread_mutex_unlock(&data.mutex);
    ret=pthread_mutex_destroy(&data.mutex);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_destroy");
    return 0;
}

