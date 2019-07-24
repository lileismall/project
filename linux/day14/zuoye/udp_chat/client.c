#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int sfd=socket(AF_INET,SOCK_DGRAM,0);
    ERROR_CHECK(sfd,-1,"socket");
    //开启端口
    struct sockaddr_in serveaddr;
    serveaddr.sin_family=AF_INET;
    serveaddr.sin_port=htons(atoi(argv[2]));
    serveaddr.sin_addr.s_addr=inet_addr(argv[1]);
    char buf[128]={0};
    //先发一个字节把自己的信息发过去
    sendto(sfd,buf,1,0,(struct sockaddr*)&serveaddr,sizeof(serveaddr));
    fd_set rdset;
    int ret;
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(sfd,&rdset);
        ret=select(sfd,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(sfd,&rdset))
        {
            memset(buf,0,sizeof(buf)-1);
            recvfrom(sfd,buf,sizeof(buf)-1,0,NULL,NULL);
            printf("%s\n",buf);
        }
        if(FD_ISSET(STDIN_FILENO,&rdset))
        {
            memset(&buf,0,sizeof(buf));
            read(STDIN_FILENO,buf,sizeof(buf)-1);
            sendto(sfd,buf,strlen(buf)-1,0,(struct sockaddr*)&serveaddr,sizeof(serveaddr));
        }
    }
    close(sfd);
    return 0;
}

