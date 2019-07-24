#include <func.h>

int main()
{
    int fd=open("file",O_RDWR);
    struct iovec iov[2];
    iov[0].iov_base="hello";
    iov[0].iov_len=5;
    iov[1].iov_base="world";
    iov[1].iov_len=5;
    writev(fd,iov,2);
    close(fd);
    return 0;
}

