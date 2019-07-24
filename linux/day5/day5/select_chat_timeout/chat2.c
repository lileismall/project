#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int fdr,fdw;
    fdw=open(argv[1],O_WRONLY);
    ERROR_CHECK(fdw,-1,"open");
    fdr=open(argv[2],O_RDONLY);
    ERROR_CHECK(fdr,-1,"open");
    printf("I am chat1,fdr=%d,fdw=%d\n",fdr,fdw);
    char buf[128]={0};
    fd_set rdset;
    int fdReadyNum;
    int ret;
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(fdr,&rdset);
        fdReadyNum=select(fdr+1,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&rdset))//标准输入可读，就读标准输入
        {
            memset(buf,0,sizeof(buf));
            ret=read(STDIN_FILENO,buf,sizeof(buf)-1);//这里会阻塞
            if(0==ret)
            {
                printf("close\n");
                break;
            }
            write(fdw,buf,strlen(buf)-1);
        }
        if(FD_ISSET(fdr,&rdset))//管道可读，就读管道
        {
            memset(buf,0,sizeof(buf));
            ret=read(fdr,buf,sizeof(buf));//这里会阻塞
            if(0==ret)
            {
                printf("byebye\n");
                break;
            }
            printf("%s\n",buf);
        }
    }
    return 0;
}

