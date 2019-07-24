#include "func.h"
#define NUM 1+2
int main()
{
	int *p;
	int arr[3]={1,2,3};
	int i=NUM*NUM;
	int j=10;
	arr[2]=4;
	p=arr;
	printf("i=%d\n",i);
	for(i=0;i<5;i++)
	{
		printf("Hello world\n");
	}
	return 0;
}
