#include <func.h>
void* threadFunc(void* p)
{
    printf("I am child thread\n");
    sleep(1);
    printf("after sleep\n");
    return NULL;
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
    printf("child cancel return=%ld\n",threadRet);
    return 0;
}

