#include <func.h>

int main(int argc,char* argv[])
{
    int pid=fork();
    if(pid==0)
    {
        exit(10);
    }else{
        sleep(20);
    }
}

