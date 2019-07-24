#include <func.h>

typedef struct{
    pid_t pid; //子进程的pid
    int fd; //管道的一端
    short busy;  //标记是否忙碌，0代表不忙碌，1代表忙碌
}process_data;



int MakeChild(process_data* p,int processNum);
int ChildHandle(int fd);
int tcp_init(const char* ip,char* port);
int sendFd(int,int);
int recvFd(int,int*);
