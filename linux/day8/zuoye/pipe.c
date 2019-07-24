#include <func.h>

int main(int argc,char* argv[])
{
    int fd[2]={0};
    pipe(fd);
    char buf[1024]={0};
    if(!fork())
    {
        write(fd[1],"i am test",9);
    }
    else
    {
        sleep(1);
        read(fd[0],buf,10);
        puts(buf);
    }
    return 0;
}

