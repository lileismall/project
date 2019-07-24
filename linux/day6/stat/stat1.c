#include <func.h>

int main(int argc,char* argv[])
{
    struct stat buf;
    stat(argv[1],&buf);
    printf("%d",buf.st_gid);
    return 0;
}

