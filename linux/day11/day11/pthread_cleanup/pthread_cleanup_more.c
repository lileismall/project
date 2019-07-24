#include <func.h>
void cleanupFunc(void *p)
{
    printf("I am cleanup Func %ld\n",(long)p);
}
void* threadFunc(void* p)
{
    pthread_cleanup_push(cleanupFunc,(void*)1);
    pthread_cleanup_push(cleanupFunc,(void*)2);
    printf("I am child thread\n");
    pthread_exit(NULL);
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
}
int main()
{
    pthread_t pthid;
    int ret;
    ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    if(ret!=0)
    {
        printf("%s:%s\n","pthread_create",strerror(ret));
        return -1;
    }
    ret=pthread_cancel(pthid);
    THREAD_ERROR_CHECK(ret,"pthread_cancel");
    long threadRet;
    ret=pthread_join(pthid,(void**)&threadRet);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("child cancel return=%ld\n",threadRet);
    return 0;
}

