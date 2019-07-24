#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    int msgid=msgget(2000,IPC_CREAT|0600);
    struct msgbuf{
        long mytype;
        char msgtext[128];   //不能超过4k
    };
    struct msgbuf buf;
    buf.mytype=atoi(argv[1]);   //第一个参数写队列类型，要大于0
    strcpy(buf.msgtext,"i am test");
    int ret=msgsnd(msgid,&buf,strlen(buf.msgtext),0);
    ERROR_CHECK(ret,-1,"msgsnd");
    return 0;

}

