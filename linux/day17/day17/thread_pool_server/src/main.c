#include "factory.h"

int main(int argc,char *argv[])
{
    if(argc!=5)
    {
        printf("./server ip port threadNum capacity\n");
        return -1;
    }
    Factory_t threadMainData; //创建含有队列及各种信息的结构体
    int threadNum=atoi(argv[3]); //创建的线程数
    int capacity=atoi(argv[4]);  //负载能力
    factoryInit(&threadMainData,threadNum,capacity); //初始化这个结构体
    factoryStart(&threadMainData);  //启动线程池
    int socketFd,newFd;  //创建套接字
    tcpInit(&socketFd,argv[1],argv[2]); 
    pQue_t pq=&threadMainData.que;   //将结构体中的队列单独拿出来，避免代码太长
    pNode_t pNew;
    while(1)
    {
        newFd=accept(socketFd,NULL,NULL); //一旦客户端有人连接就生成一个新的套接字用来传递信息
        pNew=(pNode_t)calloc(1,sizeof(Node_t)); //队列是用链表实现的，创建一个链表结点
        pNew->newFd=newFd; 
        //放入队列,为了避免线程从队列中取任务时发生冲突，这里要加锁
        pthread_mutex_lock(&pq->mutex);
        queInsert(pq,pNew); //尽量在锁的内部执行少的代码，比如将创建新的结点和通知线程有新任务都要放在外面
        pthread_mutex_unlock(&pq->mutex); 
        //通知子线程有任务
        pthread_cond_signal(&threadMainData.cond);
    }
    return 0;
}

