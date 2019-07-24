#include <func.h>
void* threadFunc(void* p)
{
    while(1)
    {
        pthread_testcancel();
    }
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
    pthread_join(pthid,NULL);
    return 0;
}

