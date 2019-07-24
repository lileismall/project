#include <func.h>


int tcp_init(const char* ip,char* port)  //用于初始化操作
{
    int sfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sfd,-1,"socket");
    struct sockaddr_in serve_addr;
    bzero(&serve_addr,sizeof(serve_addr));
    serve_addr.sin_family=AF_INET;
    serve_addr.sin_port=htons(atoi(port));
    serve_addr.sin_addr.s_addr=inet_addr(ip);
    int ret=bind(sfd,(struct sockaddr*)&serve_addr,sizeof(serve_addr));
    ERROR_CHECK(ret,-1,"bind");
    listen(sfd,10);
    return sfd;
}
