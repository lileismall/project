#include <func.h>

int main()
{
    signal(SIGINT,SIG_IGN);
    sleep(5);
    signal(SIGINT,SIG_DFL);
    return 0;
}

