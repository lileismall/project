#include "tcp_net_func.h"
int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int sfd=tcp_connect(argv[1],atoi(argv[2]));
    ERROR_CHECK(sfd,-1,"tcp_connect");
    char buf[512]={0};
    send(sfd,"come form client",15,0);
    recv(sfd,buf,sizeof(buf),0);
    puts(buf);
    close(sfd);
    return 0;
}

