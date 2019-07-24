#include <stdio.h>
#include <string.h>

typedef struct{
	int num;
	char name[20];
	float score;
}Stu;

int main()
{
	Stu student={0};
	char buf[50]="1010 lilei 99.9";
	sscanf(buf,"%d%s%f",&student.num,student.name,&student.score);
	printf("%d %s %5.2f\n",student.num,student.name,student.score);
	return 0;
}
