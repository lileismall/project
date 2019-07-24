#include <func.h>

int main(int argc,char* argv[])
{
    int pid=fork();
    if(pid==0)
    {
        while(1);
    }else{
        exit(0);
    }
}

