#include <stdio.h>
#define NUM 1+2
void print()
{
	int i;
	for(i=0;i<5;i++)
	{
		printf("Hello world\n");
	}
}
int main(int argc,char* argv[])
{
	int i;
	for(i=0;i<argc;i++)
	{
		puts(argv[i]);
	}
	int *p;
	int arr[3]={1,2,3};
	int j=10;
	arr[2]=4;
	p=arr;
	printf("i=%d\n",i);
	print();
	return 1;
}
