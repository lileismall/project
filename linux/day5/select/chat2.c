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
	fd_set rdset;
	int n;
	struct timeval val;
	int ret;
	while(1)
	{
		FD_ZERO(&rdset);
		FD_SET(STDIN_FILENO,&rdset);
		FD_SET(fdr,&rdset);
		val.tv_sec=3;
		val.tv_usec=0;
		n=select(fdr+1,&rdset,NULL,NULL,&val);
		if(n>0)
		{
			if(FD_ISSET(fdr,&rdset))//标准输入可读，就读标准输入
			{
				memset(buf,0,sizeof(buf));
				ret=read(fdr,buf,sizeof(buf)-1);
				if(0==ret)
				{
					printf("再见");
					break;
				}
				printf("%s\n",buf);
			}
			if(FD_ISSET(STDIN_FILENO,&rdset))
			{
				memset(buf,0,sizeof(buf));
				ret=read(STDIN_FILENO,buf,sizeof(buf)-1);
				if(ret==0)
				{
					printf("close");
					break;
				}
				write(fdw,buf,strlen(buf)-1);
			}
		}
		else
		{
			printf("timeout\n");
		}
	}
}
