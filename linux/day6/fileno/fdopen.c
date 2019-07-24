#include <func.h>

int main(int argc,char* argv[])
{
    int fd;
    fd=open(argv[1],O_RDWR);
    FILE* fp;
    fp=fdopen(fd,"rb+");
    char buf[10]="test";
    fwrite(buf,sizeof(char),4,fp);
    return 0;

}

