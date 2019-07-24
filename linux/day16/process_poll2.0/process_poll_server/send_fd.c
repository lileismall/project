#include "process_poll.h"

int sendFd(int fds,int fd)  //像fds发送fd描述符
{
    struct msghdr msg;
    memset(&msg,0,sizeof(msg));
    struct iovec iov[1];   //这里必须得指定长度
    char buf[10]="test";
    iov[0].iov_base=buf;  //这里必须写点东西，内核用来确认信息用
    iov[0].iov_len=2;
    msg.msg_iov=iov;
    msg.msg_iovlen=1;
    struct cmsghdr *cmsg;
    int len=CMSG_LEN(sizeof(int));
    cmsg=(struct cmsghdr*)calloc(1,len);
    cmsg->cmsg_level=SOL_SOCKET;
    cmsg->cmsg_type=SCM_RIGHTS;
    cmsg->cmsg_len=len;
    *(int*)CMSG_DATA(cmsg)=fd;
    msg.msg_control=cmsg;
    msg.msg_controllen=len;
    int ret=sendmsg(fds,&msg,0);
    ERROR_CHECK(ret,-1,"sendmsg");
    return 0;
}

int recvFd(int fds,int *fd)  //像fds发送fd描述符
{
    struct msghdr msg;
    memset(&msg,0,sizeof(msg));
    char buf1[10]={0};
    struct iovec iov[1];
    iov->iov_base=buf1;
    iov->iov_len=2;
    msg.msg_iov=iov;
    msg.msg_iovlen=1;
    struct cmsghdr *cmsg;
    int len=CMSG_LEN(sizeof(int));
    cmsg=(struct cmsghdr*)calloc(1,len);
    cmsg->cmsg_level=SOL_SOCKET;
    cmsg->cmsg_type=SCM_RIGHTS;
    cmsg->cmsg_len=len;
    msg.msg_control=cmsg;
    msg.msg_controllen=len;
    int ret=recvmsg(fds,&msg,0);
    ERROR_CHECK(ret,-1,"sendmsg");
    *fd=*(int*)CMSG_DATA(cmsg);
    return 0;
}
