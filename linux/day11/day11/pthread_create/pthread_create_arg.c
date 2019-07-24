#include <func.h>
void print()
{
    printf("I am print\n");
    pthread_exit(NULL);
}
void* threadFunc(void* p)
{
    printf("I am child thread,%s\n",(char*)p);
    print();
    printf("after print\n");
    free(p);
    return NULL;
}
int main()
{
    pthread_t pthid;
    int ret;
    char *p=(char*)malloc(20);
    strcpy(p,"hello");
    ret=pthread_create(&pthid,NULL,threadFunc,p);
    if(ret!=0)
    {
        printf("%s:%s\n","pthread_create",strerror(ret));
        return -1;
    }
    printf("I am main thread\n");
    pthread_join(pthid,NULL);
    return 0;
}

