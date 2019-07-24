#include <func.h>

int main(int argc,char *argv[])
{
	int fd,fd0,fd1,fd2;
	fd=open("log1",O_RDWR);
	fd0=open("log2",O_RDWR);
	ERROR_CHECK(fd,-1,"open");
	printf("\n");
	//close(STDOUT_FILENO);
	//close(STDERR_FILENO);
	fd1=dup2(fd,STDOUT_FILENO);
	fd2=dup2(fd0,STDERR_FILENO);
	perror("function is ok\n");
	char str[100]={0};
	printf("hello\n");
}
