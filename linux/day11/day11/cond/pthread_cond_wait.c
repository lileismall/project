#include <func.h>
typedef struct{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}threadInfo_t;
void* threadFunc(void *p)
{
    threadInfo_t *pData=(threadInfo_t*)p;
    int ret;
    printf("before wait\n");
    pthread_mutex_lock(&pData->mutex);
    ret=pthread_cond_wait(&pData->cond,&pData->mutex);
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
    sleep(4);
    ret=pthread_cond_signal(&data.cond);   //像子进程发送启动信号
    THREAD_ERROR_CHECK(ret,"pthread_cond_signal");
    printf("signal ok\n");
    pthread_join(pthid,NULL);
    return 0;
}

