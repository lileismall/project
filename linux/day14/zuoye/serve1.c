#include "tcp_net_func.h"

int main(int argc,char* argv[])
{
    int sfd=tcp_init(argv[1],atoi(argv[2]));
    ERROR_CHECK(sfd,-1,"tcp_init");
    ARGS_CHECK(argc,3);
    struct sockaddr_in clientaddr;
    char buf[512]={0};
    fd_set rdset,needMoset;
    FD_ZERO(&needMoset); //这里一定要清空
    FD_SET(sfd,&needMoset);
    FD_SET(STDIN_FILENO,&needMoset);
    int readyFdCount;
    int ret;
    int newFd;
    while(1)
    {
        //printf("this is line :%d\n",__LINE__);
        FD_ZERO(&rdset);
        memcpy(&rdset,&needMoset,sizeof(fd_set));
        readyFdCount=select(15,&rdset,NULL,NULL,NULL);
        if(readyFdCount>0)
        {
            printf("this is line :%d\n",__LINE__);
            if(FD_ISSET(sfd,&rdset))
            {
                printf("this is line :%d\n",__LINE__);
                bzero(&clientaddr,sizeof(clientaddr));
                socklen_t addrlen=sizeof(clientaddr);
                newFd=accept(sfd,(struct sockaddr*)&clientaddr,&addrlen);
                ERROR_CHECK(newFd,-1,"accept");
                printf("client ip:%s,client part:%d\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
                FD_SET(newFd,&needMoset);
            }
            if(FD_ISSET(newFd,&rdset))
            {
                memset(&buf,0,sizeof(buf));
                printf("this is line :%d\n",__LINE__);
                ret=recv(newFd,buf,sizeof(buf),0);
                if(ret==0)
                {
                    printf("与%s断开连接\n",inet_ntoa(clientaddr.sin_addr));
                    close(newFd);
                    FD_CLR(newFd,&needMoset);
                }else
                {
                    printf("%s\n",buf);
                }
            }
            if(FD_ISSET(STDIN_FILENO,&rdset))
            {
                memset(buf,0,sizeof(buf));
                printf("this is line :%d\n",__LINE__);
                ret=read(STDIN_FILENO,buf,sizeof(buf)-1);
                if(ret==0)
                {
                    printf("服务器断开连接\n");
                    break;
                }
                send(newFd,buf,strlen(buf)-1,0);
            }
        }
    }
    close(sfd);
    return 0;
}

