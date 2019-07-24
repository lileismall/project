#include <func.h>

void myDaemon()
{
    if(fork())
    {
        exit(0);
    }
    setsid();
    chdir("/");
    umask(0);
    int i;
    for(i=0;i<3;i++)
    {
        close(i);
    }
}
int main()
{
    myDaemon();
    while(1);
    return 0;
}

