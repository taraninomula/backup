#include<stdio.h>
enum week
{
	MONDAY=4,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	SUNDAY,
};
int main()
{
	enum week day;
	int i;
	day=MONDAY;
	for(i=day;i<=SUNDAY;i++)
	{
		printf("%d\n",i);
	}
}
