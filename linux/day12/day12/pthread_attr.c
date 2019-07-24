#include <func.h>
void* threadFunc(void* p)
{
    printf("I am child thread\n");
    return NULL;
}
int main()
{
    pthread_t pthid;
    int ret;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    ret=pthread_create(&pthid,&attr,threadFunc,NULL);
    if(ret!=0)
    {
        printf("%s:%s\n","pthread_create",strerror(ret));
        return -1;
    }
    ret=pthread_join(pthid,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("join success\n");
    return 0;
}

