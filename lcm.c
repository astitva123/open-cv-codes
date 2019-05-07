#include <stdio.h>

int gcd(int a,int b)
{
    if(b%a==0) return a;
    else return gcd(b%a,a);
}

int main()
{
	int t,a,b,i,lcm;
	scanf("%d",&t);

	for(i=0;i<t;i++)
	{
		scanf("%d %d",&b,&a);
		if(b>a) lcm=gcd(a,b);
		else lcm=gcd(b,a);
		printf("\n lcm is : %d",a*b/lcm);

	}

	return 0;
}