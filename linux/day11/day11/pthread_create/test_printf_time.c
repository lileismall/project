#include <func.h>

int main()
{
    struct timeval start,end;
    gettimeofday(&start,NULL);
    printf("I hen shuai\n");
    gettimeofday(&end,NULL);
    printf("printf use time=%ld\n",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
    return 0;
}

