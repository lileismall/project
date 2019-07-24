#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int sigNum=atoi(argv[1]);
    int pid=atoi(argv[2]);
    int ret;
    ret=kill(pid,sigNum);
    ERROR_CHECK(ret,-1,"kill");
    return 0;
}

