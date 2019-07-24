#include <func.h>

void func(void* args)
{
    printf("i am clean\n");
}

void* Func(void *args)
{
    pthread_cleanup_push(func,NULL);
    for(int i=0;i<10;i++);
    sleep(1);
    pthread_exit((void*)2);
    pthread_cleanup_pop(1);

}

int main(int argc,char* argv[])
{
    pthread_t pthid;
    pthread_create(&pthid,NULL,Func,NULL);
    sleep(1);
    pthread_cancel(pthid);
    int retu;
    pthread_join(pthid,(void**)&retu);
    printf("i am join retu : %d\n",retu);  //如果子线程在main线程退出前退出，返回-1，否则返回pthread_exit（）的参数
    return 0;
}

