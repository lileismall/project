#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
   int fd;
   FILE* fp=fopen(argv[1],"rb+");
   fd=fileno(fp);
   char buf[1024]="test";
   write(fd,buf,strlen(buf));
   return 0;
}

