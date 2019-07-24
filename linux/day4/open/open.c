#include <func.h>

typedef struct stu{
	int num;
	char name[20];
	float score;
}stu;

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,2);
	stu stu[3];
	char buf[30]={0};
	stu[0].num=101;strcpy(stu[0].name,"lele");stu[0].score=99;
	int fd=open(argv[1],O_RDWR|O_CREAT|O_EXCL,0666);
	ERROR_CHECK(fd,-1,"open");
	sprintf(buf,"%d %s %5.2f",stu[0].num,stu[0].name,stu[0].score);
	write(fd,buf,strlen(buf));
	lseek(fd,0,SEEK_SET);
	memset(buf,0,sizeof(buf));
	read(fd,buf,sizeof(buf)-1);
	puts(buf);
	close(fd);
	return 0;
}
