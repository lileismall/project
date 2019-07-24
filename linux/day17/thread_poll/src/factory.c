#include "factory.h"

int factory_init(Factory_t *data,int threadNum,int capacity)
{
    que_init(&data->que,capacity);
    pthread_cond_init(&data->cond,NULL);
    data->pthid=(pthread_t*)calloc(threadNum,sizeof(pthread_t));
    data->threadNum=threadNum;
    data->startFlag=0;
    return 0;
}

void* handle_func(void* QueData)
{
    Factory_t *pq=(Factory_t*)QueData;
    que_t *que=&pq->que;
    int getSuccess;
    tag_node *pCur;
    while(1)
    {
        pthread_mutex_lock(&que->mutex);
        if(!que->que_size)
        {
            pthread_cond_wait(&pq->cond,&que->mutex);
        }
        getSuccess=que_get(que,&pCur);
        pthread_mutex_unlock(&que->mutex);
        printf("newFd=%d",pCur->newFd);
        if(!getSuccess)
        {
            tran_file(pCur->newFd);
            free(pCur);
        }
        pCur=NULL;
    }
    return 0;
}

int factory_start(Factory_t* QueData)
{
    int i;
    if(!QueData->startFlag)
    {
        for(i=0;i<QueData->threadNum;i++)
        {
            pthread_create(QueData->pthid+i,NULL,handle_func,QueData);
        }
        QueData->startFlag=1;
    }
    return 0;
}
