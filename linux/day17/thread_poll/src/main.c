#include "factory.h"

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,5);
    Factory_t QueData;
    int threadNum=atoi(argv[3]);
    int capacity=atoi(argv[4]);
    factory_init(&QueData,threadNum,capacity);
    factory_start(&QueData);
    int sockFd;
    tcpInit(&sockFd,argv[1],argv[2]);
    int newFd;
    que_t *que=&QueData.que;
    while(1)
    {
        newFd=accept(sockFd,NULL,NULL);
        tag_node *node=(tag_node*)calloc(1,sizeof(tag_node));
        node->newFd=newFd;
        pthread_mutex_lock(&que->mutex);
        que_insert(&QueData.que,newFd);
        pthread_mutex_unlock(&que->mutex);
        pthread_cond_signal(&QueData.cond);
    }
    return 0;
}

