#include "process_pool.h"
int sendFd(int fds,int fd)
{
    struct msghdr msg;
    memset(&msg,0,sizeof(msg));
    struct iovec iov[2];
    iov[0].iov_base="hello";
    iov[0].iov_len=5;
    iov[1].iov_base="world";
    iov[1].iov_len=5;
    msg.msg_iov=iov;
    msg.msg_iovlen=2;
    struct cmsghdr *cmsg;
    int len=CMSG_LEN(sizeof(int));
    cmsg=(struct cmsghdr*)calloc(1,len);
    cmsg->cmsg_len=len;
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    *(int*)CMSG_DATA(cmsg)=fd;
    msg.msg_control=cmsg;
    msg.msg_controllen=len;
    int ret=sendmsg(fds,&msg,0);
    ERROR_CHECK(ret,-1,"sendmsg");
    return 0;
}
int recvFd(int fds,int *fd)
{
    struct msghdr msg;
    memset(&msg,0,sizeof(msg));
    char buf1[10]={0};
    char buf2[10]={0};
    struct iovec iov[2];
    iov[0].iov_base=buf1;
    iov[0].iov_len=5;
    iov[1].iov_base=buf2;
    iov[1].iov_len=5;
    msg.msg_iov=iov;
    msg.msg_iovlen=2;
    struct cmsghdr *cmsg;
    int len=CMSG_LEN(sizeof(int));
    cmsg=(struct cmsghdr*)calloc(1,len);
    cmsg->cmsg_len=len;
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    msg.msg_control=cmsg;
    msg.msg_controllen=len;
    int ret=recvmsg(fds,&msg,0);
    ERROR_CHECK(ret,-1,"sendmsg");
    *fd=*(int*)CMSG_DATA(cmsg);
    return 0;
}
