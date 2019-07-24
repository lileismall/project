#include <func.h>
typedef struct{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}threadInfo_t;
void* threadFunc(void *p)
{
    threadInfo_t *pData=(threadInfo_t*)p;
    int ret;
    struct timespec t;
    t.tv_sec=5+time(NULL);//绝对时间
    t.tv_nsec=0;
    pthread_mutex_lock(&pData->mutex);
    ret=pthread_cond_timedwait(&pData->cond,&pData->mutex,&t);
    pthread_mutex_unlock(&pData->mutex);
    printf("I am child %d\n",ret);
    pthread_exit(NULL);
}
int main()
{
    threadInfo_t data;
    pthread_mutex_init(&data.mutex,NULL);
    pthread_cond_init(&data.cond,NULL);
    pthread_t pthid;
    pthread_create(&pthid,NULL,threadFunc,&data);
    int ret; 
    usleep(1000);
    ret=pthread_cond_signal(&data.cond);
    THREAD_ERROR_CHECK(ret,"pthread_cond_signal");
    printf("signal ok\n");
    pthread_join(pthid,NULL);
    return 0;
}

