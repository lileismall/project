#include <func.h>
void* threadFunc(void* p)
{
    printf("I am child thread\n");
    return (void*)0;
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
    long childRet;
    ret=pthread_join(pthid,(void**)&childRet);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("I am main,%ld\n",childRet);
    return 0;
}

