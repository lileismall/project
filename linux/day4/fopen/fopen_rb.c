#include <stdio.h>

int main(int argc,char* argv[])
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	FILE *fp;
	fp=fopen(argv[1],"rb+");
	if(!fp)
	{
		perror("fopen");
		return -1;
	}
	char buf[50]={0};
	long pos;
	fread(buf,sizeof(char),5,fp);
	pos=ftell(fp);
	printf("buf=%s,pos=%ld\n",buf,pos);
	fclose(fp);
	return 0;
}
