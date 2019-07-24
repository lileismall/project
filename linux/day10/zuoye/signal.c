#include <func.h>
void Handler(int signum)
{
    printf("%d is coming\n",signum);
    sleep(3);
    printf("%d is ending\n",signum);
}
int main(int argc,char* argv[])
{
    signal(SIGINT,Handler);
    while(1);
}

