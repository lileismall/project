#include <func.h>

typedef struct{
    int tickets;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}threadInfo;

void* windows1(void* p)
{
    threadInfo* data=(threadInfo*)p;
    while(1)
    {
        pthread_mutex_lock(&data->mutex);
        if(data->tickets>0)
        {
            printf("i am windows1,i qiangdao 1\n");
            data->tickets--;
            printf("the tickets is %d\n",data->tickets);
            if(!data->tickets)
            {
                sleep(5);  //票卖完后，5秒后再次发票
                pthread_cond_signal(&data->cond);
            }
            pthread_mutex_unlock(&data->mutex);
            usleep(1000);
        }
        else{
            pthread_mutex_unlock(&data->mutex);
            break;
        }
    }
    pthread_exit((void*)2);
}

void* windows2(void* p)
{
    threadInfo* data=(threadInfo*)p;
    while(1)
    {
        pthread_mutex_lock(&data->mutex);
        if(data->tickets>0)
        {
            printf("i am windows2,i qiangdao 1\n");
            data->tickets--;
            printf("the tickets is %d\n",data->tickets);
            if(!data->tickets)
            {
                sleep(5);  //票卖完后，5秒后再次发票
                pthread_cond_signal(&data->cond);
            }
            pthread_mutex_unlock(&data->mutex);
            usleep(1000);
        }
        else{
            pthread_mutex_unlock(&data->mutex);
            break;
        }
    }
    pthread_exit((void*)2);
}

void* sales(void* p)
{
    threadInfo* data=(threadInfo*)p;
    pthread_mutex_lock(&data->mutex);
    if(data->tickets>0)
    {
        pthread_cond_wait(&data->cond,&data->mutex);    //等待信号的到来
    }
    data->tickets=20;
    pthread_mutex_unlock(&data->mutex);
    pthread_exit((void*)2);
}

//创建三个子进程，窗口1,2，放票
int main(int argc,char* argv[])
{
    //pthread_t *pthid[3];
    pthread_t pthid1,pthid2,pthid3;
    threadInfo data;
    data.tickets=10;
    pthread_mutex_init(&data.mutex,NULL);
    pthread_cond_init(&data.cond,NULL);
    pthread_create(&pthid1,NULL,windows1,&data);
    pthread_create(&pthid2,NULL,windows2,&data);
    pthread_create(&pthid3,NULL,sales,&data);
    printf("fjd");
    pthread_join(pthid1,NULL);
    pthread_join(pthid2,NULL);
    pthread_join(pthid3,NULL);
    return 0;

}
