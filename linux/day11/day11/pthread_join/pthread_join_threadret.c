#include <func.h>
void* threadFunc(void* p)
{
    char *pStr=(char*)malloc(20);
    strcpy(pStr,"I hen niu");
    return pStr;
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
    char *pChildRet;
    ret=pthread_join(pthid,(void**)&pChildRet);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("I am main,%s\n",pChildRet);
    return 0;
}

