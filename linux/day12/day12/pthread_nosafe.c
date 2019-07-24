#include <func.h>
void* threadFunc(void* p1)
{
    time_t now;
    now=time(NULL);
    char *p=ctime(&now);
    printf("I am child thread %s\n",p);
    sleep(5);
    printf("I am child thread %p %s\n",p,p);
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
    sleep(3);
    time_t now;
    now=time(NULL);
    char *p=ctime(&now);
    printf("I am main thread %p %s\n",p,p);
    ret=pthread_join(pthid,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("join success\n");
    return 0;
}

