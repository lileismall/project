#include <func.h>
void* threadFunc(void* p)
{
    printf("I am child thread,%ld\n",(long)p);
    return NULL;
}
int main()
{
    pthread_t pthid1,pthid2;
    int ret;
    ret=pthread_create(&pthid1,NULL,threadFunc,(void*)1);
    if(ret!=0)
    {
        printf("%s:%s\n","pthread_create",strerror(ret));
        return -1;
    }
    ret=pthread_create(&pthid2,NULL,threadFunc,(void*)2);
    pthread_join(pthid1,NULL);
    pthread_join(pthid2,NULL);
    return 0;
}

