#include <func.h>
void* threadFun(void *p)
{
    printf("%ld\n",(long)p);
    pthread_exit((void*)2);
}
int main(int argc,char* argv[])
{
    pthread_t pthid;
    int ret;
    ret=pthread_create(&pthid,NULL,threadFun,(void*)1);
    if(ret)
    {
        printf("%s:%s\n","pthread_create",strerror(ret));
        return -1;
    }
    long rret;
    pthread_join(pthid,(void**)&rret);
    printf("%ld\n",rret);
    return 0;
}

