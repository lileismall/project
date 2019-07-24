#include <stdio.h>
#define NUM 1+2
int main()
{
	int *p;
	int arr[3]={1,2,3};
	long i=NUM*NUM;
	char j=i;
	arr[2]=4;
	p=arr;
	printf("i=%ld\n",i);
	for(i=0;i<5;i++)
	{
		printf("Hello world\n");
	}
	return 0;
}
