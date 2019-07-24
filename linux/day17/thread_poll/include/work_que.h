#ifndef __WORK_QUE__
#define __WORK_QUE__

#include "head.h"
typedef struct tag_node{
    int newFd;
    struct tag_node *pNext;
}tag_node;

typedef struct tag_que
{
    tag_node *que_head,*que_tail;
    int que_capacity;
    int que_size;
    pthread_mutex_t que_mutex;
}que_t;
int que_init(que_t *q,int capacity);
int que_fet(que_t *q,tag_node** p);
#endif
