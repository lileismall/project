#include <func.h>
void cleanupFunc(void *p)
{
    free(p);
    printf("free success\n");
}
void* threadFunc(void* p)
{
    p=malloc(20);
    pthread_cleanup_push(cleanupFunc,p);
    strcpy((char*)p,"hello");
    printf("I am child thread,%s\n",(char*)p);
    pthread_exit(NULL);
    pthread_cleanup_pop(0);
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
    //ret=pthread_cancel(pthid);
    //THREAD_ERROR_CHECK(ret,"pthread_cancel");
    long threadRet;
    ret=pthread_join(pthid,(void**)&threadRet);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("child exit return=%ld\n",threadRet);
    return 0;
}

