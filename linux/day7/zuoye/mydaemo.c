#include <func.h>

int main(int argc,char* argv[])
{
    int pid=fork();
    if(!pid)
    {
        exit(0);
    }
    setsid();   //自己成为组长，脱离控制端
    umask(0);
    for(int i=0;i<10;i++)//关闭继承来的文件，这里主要是标准输入输出0，1，2
    {
        close(i);
    }
    chdir("/");     //将目录更改为根目录
    int fd=open("./tmp/log",O_WRONLY);
    ERROR_CHECK(fd,-1,"open");
    while(1)
    {
        sleep(5);
        write(fd,"wohenshuai\n",11);
    }
    return 0;
}

