#include <func.h>

int printDir(char *path,int width)
{
	DIR* dir;
	dir=opendir(path);
	ERROR_CHECK(dir,NULL,"opendir");
	struct dirent *p;
	//char tmPath[1024]={0};
	while((p=readdir(dir))!=NULL)
	{
		printf("%d %d %s\n",p->d_reclen,p->d_type,p->d_name);
	}
}

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,2);
	puts(argv[1]);
	printDir(argv[1],4);
}
