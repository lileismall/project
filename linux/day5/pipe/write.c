#include <func.h>

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,3);
	int fdr,fdw;
	char buf[1024]={0};
	fdw=open(argv[1],O_WRONLY);
	ERROR_CHECK(fdw,-1,"open");
	fdr=open(argv[2],O_RDONLY);
	ERROR_CHECK(fdr,-1,"open");
	while(1)
	{
		memset(buf,0,sizeof(buf)-1);
		read(STDIN_FILENO,buf,sizeof(buf)-1);
		write(fdw,buf,strlen(buf));
		memset(buf,0,sizeof(buf)-1);
		read(fdr,buf,sizeof(buf)-1);
		printf("%s",buf);
	}
}
