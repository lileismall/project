#include <stdio.h>
#include <string.h>

typedef struct{
	int num;
	char name[20];
	float score;
}Stu;

int main()
{
	Stu student={1010,"lilei",99.9};
	char buf[50];
	memset(buf,0,sizeof(buf));
	sprintf(buf,"%d %s %5.2f",student.num,student.name,student.score);
	printf("%s\n",buf);
	return 0;
}
