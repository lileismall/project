#include <func.h>

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,2);
	DIR *dir;
	dir=opendir(argv[1]);
	ERROR_CHECK(dir,NULL,"opendir");
	struct dirent *p;
	struct stat buf;
	int ret=0;
	char path[1024]={0};
	char time[100]={0};
	while((p=readdir(dir)) != NULL)
	{
		memset(path,0,sizeof(path));
		sprintf(path,"%s%s%s",argv[1],"/",p->d_name);
		ret=stat(path,&buf);
		ERROR_CHECK(ret,-1,"stat");
		sprintf(time,"%s",ctime(&buf.st_mtime));
        time[strlen(time)-6]='\0';
		printf("%ld %x %ld %s %s %ld %s %s\n",buf.st_ino,buf.st_mode,buf.st_nlink,\
	getpwuid(buf.st_uid)->pw_name,getgrgid(buf.st_gid)->gr_name,buf.st_size,time,p->d_name);
	}
}
