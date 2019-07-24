#include <func.h>

int main()
{
    int fds[2];//存储两个描述符
    pipe(fds);
    if(!fork())
    {
        close(fds[1]);//关闭写端
        char buf[128]={0};
        read(fds[0],buf,sizeof(buf));
        printf("I am child buf=%s\n",buf);
        exit(0);
    }else{
        close(fds[0]);//关闭读端  
        write(fds[1],"I hen shuai",11);
        wait(NULL);
        return 0;
    }
}

