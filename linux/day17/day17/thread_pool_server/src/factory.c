#include "factory.h"

int factoryInit(pFactory_t pf,int threadNum,int capacity)
{
    queInit(&pf->que,capacity); //初始化队列
    pthread_cond_init(&pf->cond,NULL); //初始化条件变量
    pf->pthid=(pthread_t*)calloc(threadNum,sizeof(pthread_t)); //创建一个指定线程数的指针
    pf->threadNum=threadNum; 
    pf->startFlag=0;  //初始化线程池关闭状态
    return 0;
}
//子线程函数
void *threadFunc(void *p)
{
    pFactory_t pf=(pFactory_t)p;
    pQue_t pq=&pf->que;
    pNode_t pCur;
    int getSuccess;
    while(1)
    {
        pthread_mutex_lock(&pq->mutex);
        if(!pq->size) //通过队列大小判断是否为空
        {
            pthread_cond_wait(&pf->cond,&pq->mutex);//队列为空，就睡觉
        }
        getSuccess=queGet(pq,&pCur);//从队列拿任务
        pthread_mutex_unlock(&pq->mutex);
        if(!getSuccess)
        {
            tranFile(pCur->newFd);//发文件
            free(pCur);
        }
        pCur=NULL;
    }
}
//启动线程池，循环创建线程
int factoryStart(pFactory_t pf)
{
    int i;
    if(!pf->startFlag) //如果线程池处于关闭状态
    {
        for(i=0;i<pf->threadNum;i++)
        {
            pthread_create(pf->pthid+i,NULL,threadFunc,pf); //threadFunc函数类型和参数类型都必须是void*
        }
        pf->startFlag=1;
    }
    return 0;
}

