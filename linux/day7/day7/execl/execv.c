#include <func.h>

int main()
{
    char *const argv[4]={"argv0","argv1","argv2",NULL};
    printf("I am execl\n");
    execv("./print",argv);
    printf("you can't see me\n");
    return 0;
}

