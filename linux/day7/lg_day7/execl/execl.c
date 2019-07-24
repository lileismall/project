#include <func.h>

int main()
{
    printf("I am execl\n");
    execl("./print","argv0","argv1","argv2",NULL);
    printf("you can't see me\n");
    return 0;
}

