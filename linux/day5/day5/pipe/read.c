#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fdr;
    fdr=open(argv[1],O_RDONLY);
    ERROR_CHECK(fdr,-1,"open");
    printf("I am reader,fdr=%d\n",fdr);
    char buf[128]={0};
    int ret=read(fdr,buf,sizeof(buf));
    printf("ret=%d,buf=%s\n",ret,buf);
    return 0;
}

