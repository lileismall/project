#include <func.h>

int main(int argc,char* argv[])
{
    execl("./add","add",argv[1],argv[2],NULL);  //最后一个参数一定要是NULL，以此判断为结束的
    return 0;
}

