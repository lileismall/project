#include <func.h>

int main()
{
    int fd=open("file",O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    struct stat buf;
    fstat(fd,&buf);
    char *p=(char*)mmap(NULL,buf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(!fork())
    {
        printf("I am child %s\n",p);
    }else{
        strcpy(p,"I hen shuai");
        wait(NULL);
    }
    return 0;
}

