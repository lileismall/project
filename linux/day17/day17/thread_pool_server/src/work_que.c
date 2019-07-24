#include "work_que.h"

void queInit(pQue_t pq,int capacity)
{
    memset(pq,0,sizeof(Que_t));
    pq->capacity=capacity;
    pthread_mutex_init(&pq->mutex,NULL);
}

void queInsert(pQue_t pq,pNode_t pNew)
{
    if(NULL==pq->queHead)//如果队列为空
    {
        pq->queHead=pNew;
        pq->queTail=pNew;
    }else{
        pq->queTail->pNext=pNew;
        pq->queTail=pNew;
    }
    pq->size++;
}

int queGet(pQue_t pq,pNode_t* pGet)
{
    *pGet=pq->queHead; //先进先出
    if(NULL==*pGet)
    {
        return -1;
    }
    pq->queHead=pq->queHead->pNext; //删除头部
    if(NULL==pq->queHead) //判断头部的下一个是否为NULL，如果是，将尾指针置为NULL
    {
        pq->queTail=NULL;
    }
    pq->size--; //队列长度减一
    return 0;
}
