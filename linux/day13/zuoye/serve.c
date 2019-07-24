#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int sfd=socket(AF_INET,SOCK_STREAM,0); 
    ERROR_CHECK(sfd,-1,"socket");
    struct sockaddr_in my_addr;
    bzero(&my_addr,sizeof(my_addr));
    my_addr.sin_family=AF_INET;  //采用Ipv4协议
    my_addr.sin_port=htons(atoi(argv[2])); //端口号，通常大于1024
    my_addr.sin_addr.s_addr=inet_addr(argv[1]);
    int ret=bind(sfd,(struct sockaddr*)&my_addr,sizeof(my_addr));
    ERROR_CHECK(ret,-1,"bind");
    listen(sfd,10);
    int newsfd;
    struct sockaddr_in clientaddr;
    bzero(&clientaddr,sizeof(clientaddr));
    socklen_t addrlen=sizeof(struct sockaddr);
    newsfd=accept(sfd,(struct sockaddr*)&clientaddr,&addrlen);
    ERROR_CHECK(newsfd,-1,"accept");
    printf("client ip=%s,client port=%d\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
    char buf[128]={0};
    recv(newsfd,buf,sizeof(buf),0);
    printf("serve recv=%s\n",buf);
    send(newsfd,"come form serve",15,0);
    close(sfd);
    close(newsfd);
    return 0;
}

