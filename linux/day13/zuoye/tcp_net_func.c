#include <func.h>

int tcp_init(const char* ip,int port)  //用于初始化操作
{
    int sfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sfd,-1,"socket");
    struct sockaddr_in serve_addr;
    bzero(&serve_addr,sizeof(serve_addr));
    serve_addr.sin_family=AF_INET;
    serve_addr.sin_port=htons(port);
    serve_addr.sin_addr.s_addr=inet_addr(ip);
    int ret=bind(sfd,(struct sockaddr*)&serve_addr,sizeof(serve_addr));
    ERROR_CHECK(ret,-1,"bind");
    listen(sfd,10);
    return sfd;
}

int tcp_accept(int sfd)   //用于服务端的接受
{
    struct sockaddr_in clientaddr;
    bzero(&clientaddr,sizeof(clientaddr));
    socklen_t addrlen=sizeof(clientaddr);
    int newsfd=accept(sfd,(struct sockaddr*)&clientaddr,&addrlen);
    ERROR_CHECK(newsfd,-1,"accept");
    printf("client p=%s,client port=%d\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
    return newsfd;
}


int tcp_connect(const char* ip,int port) //用于客户端的连接
{
    int sfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sfd,-1,"socket");
    struct sockaddr_in clientaddr;
    bzero(&clientaddr,sizeof(clientaddr));
    clientaddr.sin_family=AF_INET;
    clientaddr.sin_port=htons(port);
    clientaddr.sin_addr.s_addr=inet_addr(ip);
    int addrlen=sizeof(struct sockaddr);
    int ret=connect(sfd,(struct sockaddr*)&clientaddr,addrlen);
    ERROR_CHECK(ret,-1,"connect");
    return sfd;
}
