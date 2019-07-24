#include <stdio.h>

int main()
{
	int *p=NULL;
	printf("I am normal\n");
	*p=4;
	printf("you can't see me\n");
	return 0;
}
