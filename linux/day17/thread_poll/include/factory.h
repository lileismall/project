#ifndef __FACTORY_H__
#define __FACTORY_H__
#include "head.h"
#include "work_que.h"

typedef struct{
    pthread_t *pthid;
    int threadNum;
    pthread_cond_t cond;
    que_t que;
    short startFlag;
}Factory_t;

int factory_init(Factory_t*,int ,int);
int factory_start(Factory_t *QueData);
int tcpInit(int *fd,char *ip,char *port);
#endif
