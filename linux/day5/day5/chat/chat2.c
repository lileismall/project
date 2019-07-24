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
    while(1)
    {
        memset(buf,0,sizeof(buf));
        int ret=read(fdr,buf,sizeof(buf));//这里会阻塞
        printf("%s\n",buf);


        memset(buf,0,sizeof(buf));
        read(STDIN_FILENO,buf,sizeof(buf)-1);//这里会阻塞
        write(fdw,buf,strlen(buf)-1);
    }
    return 0;
}

