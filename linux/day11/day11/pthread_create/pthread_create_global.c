#include <func.h>
int global=10;
void* threadFunc(void* p)
{
    global=5;
    return NULL;
}
int main()
{
    pthread_t pthid;
    int ret;
    printf("main global=%d\n",global);
    ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    if(ret!=0)
    {
        printf("%s:%s\n","pthread_create",strerror(ret));
        return -1;
    }
    pthread_join(pthid,NULL);
    printf("main global=%d\n",global);
    return 0;
}

