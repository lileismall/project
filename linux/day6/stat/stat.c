#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    DIR *dir;
    dir=opendir(argv[1]);
    if(NULL==dir)
    {
        fprintf(stderr,"err\n");
        return 0;
    }
    chdir(argv[1]);
    struct dirent *d;
    struct stat buf;
    int i=0;
    while((d=readdir(dir)) != NULL)         //readdir每读一次，dir指针就往后偏移一个 
    {
        stat(d->d_name,&buf);
        printf("%d",i);
        printf("%ld %d\n",buf.st_ino,buf.st_gid);
    }
    return 0;
}

