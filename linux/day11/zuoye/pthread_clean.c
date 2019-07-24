#include <func.h>

void cleanupFun(void* p)
{
    printf("this is cleanupFun\n");
    free(p);
    printf("mem is freed\n");
}

void* threadFun(void* p)
{
    char *pi=(char*)malloc(20);
    pthread_cleanup_push(cleanupFun,pi);
    printf("this is child\n");
    pthread_exit((void*)0);
    pthread_cleanup_pop(0);
}
int main(int argc,char* argv[])
{
    pthread_t pthid;
    int ret;
    ret=pthread_create(&pthid,NULL,threadFun,NULL);
    if(ret)
    {
        printf("%s:%s\n","pthread_create",strerror(ret));
        return -1;
    }
    ret=pthread_cancel(pthid);
    THREAD_ERROR_CHECK(ret,"pthrad_cancel");
    pthread_join(pthid,NULL);
    return 0;
}

