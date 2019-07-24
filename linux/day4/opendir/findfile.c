#include <func.h>

int findfile(char *path,char *name)
{
	DIR* dir;
	dir=opendir(path);
	ERROR_CHECK(dir,NULL,"opendir");
	struct dirent *p;
	char tmPath[1024]={0};
	char filePath[1024]={0};
	while((p=readdir(dir))!=NULL)
	{
		if(!strcmp(p->d_name,".") || !strcmp(p->d_name,".."))
		{
			continue;
		}
		else if(!strcmp(p->d_name,name))
		{
			strcpy(filePath,getcwd(NULL,0));
			printf("%s%s%s\n",filePath,"/",name);
			return 0;
		}
		else if(4==p->d_type)
		{
			sprintf(tmPath,"%s%s%s",path,"/",p->d_name);
			findfile(tmPath,name);
			return 0;
		}
	}
}

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,3);
	puts(argv[1]);
	findfile(argv[1],argv[2]);
	return 0;
}
