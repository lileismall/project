#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <jsoncpp/json/json.h>
using namespace std;
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

void do_service(int sockfd);

int main(int argc, const char *argv[])
{
    int peerfd = socket(PF_INET, SOCK_STREAM, 0);
    if(peerfd == -1)
        ERR_EXIT("socket");

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("192.168.204.135"); //localhost
    //addr.sin_addr.s_addr = INADDR_ANY; //localhost
    addr.sin_port = htons(8888);
    socklen_t len = sizeof addr;
    if(connect(peerfd, (struct sockaddr*)&addr, len) == -1)
        ERR_EXIT("Connect");

	char buf[1024];
	memset(buf, 0, sizeof(buf));
	/* read(peerfd, buf, sizeof(buf)); */
	printf("%s\n", buf);

    do_service(peerfd);
    return 0;
}



void do_service(int sockfd)
{
    char recvbuf[1000000] = {0}; //1M
    char recvlen[100000] = {0};
    char sendbuf[1024] = {0};
    Json::Reader reader;
    Json::Value val;
    while(1)
    {
        fgets(sendbuf, sizeof sendbuf, stdin);
        write(sockfd, sendbuf, strlen(sendbuf));
		//sleep(5);

        //read
        int nreadlen = read(sockfd, recvlen,4);//接收长度
        int nread = read(sockfd, recvbuf, sizeof recvbuf);
        if(nread == -1|nreadlen == -1)
        {
            if(errno == EINTR)
                continue;
            ERR_EXIT("read");
        }
        else if(nread == 0) //代表链接断开
        {
            printf("server close!\n");
            close(sockfd);
            exit(EXIT_SUCCESS);
        }
        
        if(!reader.parse(recvbuf,val))
        {
            perror("reader.parse");
            printf("receive msg : %s\n", recvbuf);
            continue;
        }

        /* int i=1; */
        /* while(val[std::to_string(i)].asString().size()) */
        /* { */
        /*     cout << i<< "." <<val[std::to_string(i)].asString() << " "; */
        /*     i++; */
        /* } */
        /* cout << endl; */

        printf("receve msglen:\n %s \n",recvlen);
        printf("receive msg :\n %s\n", recvbuf);
        memset(recvbuf, 0, sizeof recvbuf);
        memset(sendbuf, 0, sizeof sendbuf);
    }
}




