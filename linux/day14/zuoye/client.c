#include "tcp_net_func.h"
int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int sfd=tcp_connect(argv[1],atoi(argv[2]));
    ERROR_CHECK(sfd,-1,"tcp_connect");
    char buf[512]={0};
    fd_set rdset,needMoset;
    bzero(&needMoset,sizeof(needMoset));
    FD_SET(STDIN_FILENO,&needMoset);
    FD_SET(sfd,&needMoset);
    int readyFdCount;
    int ret;
    while(1)
    {
        FD_ZERO(&rdset);
        memcpy(&rdset,&needMoset,sizeof(fd_set));
        readyFdCount=select(15,&rdset,NULL,NULL,NULL);
        if(readyFdCount>0)
        {
            if(FD_ISSET(sfd,&rdset))
            {
                memset(buf,0,sizeof(buf));
                ret=recv(sfd,buf,sizeof(buf),0);
                if(ret==0)
                {
                    printf("断开连接\n");
                    break;
                }
            }
            if(FD_ISSET(STDIN_FILENO,&rdset))
            {
                memset(&buf,0,sizeof(buf));
                read(STDIN_FILENO,buf,sizeof(buf)-1);
                send(sfd,buf,strlen(buf)-1,0);
            }
        }
    }
    close(sfd);
    return 0;
}

