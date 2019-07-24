#include <func.h>
struct msgbuf{
    long mtype;
    char mtext[128];
};
int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    int msgid=msgget(1000,IPC_CREAT|0600);
    ERROR_CHECK(msgid,-1,"msgget");
    struct msgbuf msg={0};
    int ret=msgrcv(msgid,&msg,sizeof(msg.mtext),atoi(argv[1]),IPC_NOWAIT);
    ERROR_CHECK(ret,-1,"msgrcv");
    printf("get=%s,%ld\n",msg.mtext,msg.mtype);
    return 0;
}

