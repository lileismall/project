#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd;
    fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    char *p;
    char buf[1024]="world";
    p=(char*)mmap(NULL,10,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    strcpy(p,buf);
    int ret=munmap(p,10);
    ERROR_CHECK(ret,-1,"munmap");
    return 0;
}

