#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
	int fd,fd1;
    char buf[1024]={0};
    char buf1[1024]={0};
	fd=open(argv[1],O_RDWR);
	fd1=dup(fd);
    read(fd,buf,5);
    read(fd1,buf1,5);
    puts(buf);
    puts(buf1);
	printf("fd=%d,fd1=%d\n",fd,fd1);
}
