#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    char buf[1024]="this is test";
    int fd;
    fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    write(fd,buf,strlen(buf)-1);
    lseek(fd,0,SEEK_SET);
    read(fd,buf,sizeof(buf)-1);
    puts(buf);
    return 0;
}

