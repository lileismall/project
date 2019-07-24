#include <func.h>
#define N 2
typedef struct{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}threadInfo_t;
void cleanupUnlock(void *p)
{
    threadInfo_t *pClean=(threadInfo_t*)p;
    pthread_mutex_unlock(&pClean->mutex);
    printf("unlock success\n");
}
void* threadFunc(void* p)
{
    threadInfo_t *pThread=(threadInfo_t*)p;
    pthread_mutex_lock(&pThread->mutex);
    pthread_cleanup_push(cleanupUnlock,pThread);
    pthread_cond_wait(&pThread->cond,&pThread->mutex);
    pthread_cleanup_pop(1);
    printf("wake up success\n");
    pthread_exit(NULL);
}
int main()
{
    pthread_t pthid[N];
    threadInfo_t data;
    pthread_mutex_init(&data.mutex,NULL);
    pthread_cond_init(&data.cond,NULL);
    int i,ret;
    for(i=0;i<N;i++)
    {
        pthread_create(pthid+i,NULL,threadFunc,&data);
    }
    usleep(10000);
//    for(i=0;i<N;i++)
//    {
//        ret=pthread_cancel(pthid[i]);
//        THREAD_ERROR_CHECK(ret,"pthread_cancel");
//    }

    pthread_cond_broadcast(&data.cond);
    long childRet;
    for(i=0;i<N;i++)
    {
        ret=pthread_join(pthid[i],(void**)&childRet);
        THREAD_ERROR_CHECK(ret,"pthread_join");
        printf("get childRet=%ld\n",childRet);
    }
    return 0;
}


