#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    int msgid=msgget(2000,IPC_CREAT|0600);  //创建或者获取msgid，队列标识符
    struct msgbuf{
        long mytype;
        char msgtext[128];   //不能超过4k
    };
    struct msgbuf buf;
    memset(&buf,0,sizeof(struct msgbuf));
    buf.mytype=atoi(argv[1]);   //第一个参数写队列类型，要大于0
    int ret=msgrcv(msgid,&buf,sizeof(buf.msgtext),atoi(argv[1]),0);
    ERROR_CHECK(ret,-1,"msgsnd");
    puts(buf.msgtext);
    msgctl(msgid,IPC_RMID,NULL);
    return 0;

}

