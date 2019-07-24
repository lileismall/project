#include <func.h>
typedef struct{
    pthread_mutex_t mutex;
}threadInfo;
#define  NUM 20000000
int n=0;
void* threadFunc(void *p)
{
    threadInfo *pdata=(threadInfo*)p;
    printf("this is threadFunc\n");
    int i;
    for(i=0;i<NUM;i++)
    {
        pthread_mutex_lock(&pdata->mutex);
        n++;
        pthread_mutex_unlock(&pdata->mutex);
    }
    pthread_exit((void*)0);
}
int main(int argc,char* argv[])
{
    pthread_t pthid;
    threadInfo data;
    int ret=pthread_mutex_init(&data.mutex,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_t");
    ret=pthread_create(&pthid,NULL,threadFunc,&data);
    if(ret)
    {
        printf("%s:%s\n","pthread_create",strerror(ret));
    }
    int i;
    for(i=0;i<NUM;i++)
    {
        pthread_mutex_lock(&data.mutex);
        n++;
        pthread_mutex_unlock(&data.mutex);
    }
    printf("%d\n",n);
    return 0;
}

