#include <func.h>

int main()
{
    FILE *fp;
    fp=popen("./add","w");
    ERROR_CHECK(fp,NULL,"popen");
    char buf[128]="3 4\n";
    fputs(buf,fp);
    pclose(fp);
    return 0;
}

