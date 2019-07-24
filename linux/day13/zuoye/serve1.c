#include "tcp_net_func.h"

int main(int argc,char* argv[])
{
    int sfd=tcp_init(argv[1],atoi(argv[2]));
    ARGS_CHECK(argc,3);
    while(1)
    {
        int cfd=tcp_accept(sfd);
        char buf[512]={0};
        int ret=recv(cfd,buf,sizeof(buf),0);
        ERROR_CHECK(ret,-1,"recv");
        puts(buf);
        ret=send(cfd,"come form serve",15,0);
        ERROR_CHECK(ret,-1,"send");
        close(cfd);
        
    }
    close(sfd);
    return 0;
}

