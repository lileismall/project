#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    int fdw;
    fdw=open(argv[1],O_WRONLY);
    ERROR_CHECK(fdw,-1,"open");
    printf("I am writer fdw=%d\n",fdw);
    write(fdw,"hello",5);
    return 0;
}

