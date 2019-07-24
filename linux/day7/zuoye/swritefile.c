#include <func.h>

int main(int argc,char* argv[])
{
   int fd=open("file",O_RDWR);
   ERROR_CHECK(fd,-1,"open");         //file文件对普通用户是没有写入权限的
   write(fd,argv[1],strlen(argv[1]));  //直接将命令行的参数写入文件
   return 0;
}

