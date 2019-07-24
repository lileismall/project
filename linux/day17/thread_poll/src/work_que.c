#include "work_que.h"

int que_init(que_t *pq,int capacity)
{
    memset(pq,0,sizeof(que_t));
    pq->que_capacity=capacity;
    pthread_mutex_init(&pq->mutex,NULL);
    return 0;
}

int que_get(que_t *que,tag_node **pCur)
{
    if(que->que_size)
    {
        *pCur=que->que_head;
        que->que_head=que->que_head->pNext;
        if(que->que_head==NULL)
        {
            que->que_tail=NULL;
        }
    }else{
        return -1;
    }
    que->que_size--;
    return 0;
}

int que_insert(que_t *que,int newFd)
{
    tag_node *node=(tag_node*)calloc(1,sizeof(tag_node));
    node->newFd=newFd;
    if(!que->que_size)
    {
        que->que_head=node;
        que->que_tail=node;
    }else{
        que->que_tail->pNext=node;
        que->que_tail=node;
    }
    que->que_size++;
    return 0;
}
