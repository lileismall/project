#include <func.h>

void findfile(char *path,char *filename)
{
    DIR* dir;
    dir=opendir(path);
    struct dirent *d;
    char buf[1024];
   while((d=readdir(dir)) != NULL)
    {
        if(!strcmp(d->d_name,".") || !strcmp(d->d_name,".."))
        {
            continue;
        }
        else if(!strcmp(d->d_name,filename))
        {
            printf("%s%s%s\n",path,"/",filename);
            return ;
        }
        else
        {
            if(d->d_type==4)
            {
                memset(buf,0,sizeof(buf));
                sprintf(buf,"%s%s%s",path,"/",d->d_name);
                findfile(buf,filename);
                return ;
            }
        }
    }

}



int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    findfile(argv[1],argv[2]);
}
