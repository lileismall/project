#include <func.h>
void* threadFunc(void* p)
{
    printf("I am child thread\n");
    while(1);
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
    printf("I am main thread,my thread id=%ld\n",pthread_self());
    while(1);
    usleep(1000);
    return 0;
}

