#include <stdio.h>
#include <time.h>

int main()
{
	time_t sec;;
	int sce;
	sec=time(NULL);
	sce=sec;
	printf("\nthe current time is %d\n",sce);

	return 0;
}
