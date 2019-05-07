#include <stdio.h>
#include <stdlib.h>

int main() 
{
    unsigned int m,n,i,j,t,flag=0;
    double *arrn,*arrm,*arr,k,temp;
    
    scanf("%d %d",&m,&n);
    k=n;
    
    arrn=(double*)malloc(n*sizeof(double));
    arrm=(double*)malloc(m*sizeof(double));
    //arr=(double*)malloc((n+m-1)*sizeof(double));
    
    double minm,minn,mi,ni;
    minm=0;
    maxn=0;

    for(i=0;i<m;i++)
    {    
        scanf("%lf",&arrm[i]);
        temp=arrm[i];
        if(temp<minm) {
            minm=temp;
            mi=i;
        }
    }
    for(i=0;i<n;i++)
    {
        scanf("%lf",&arrn[i]);
        temp=arrn[i];
        if(temp>maxn) {
            maxn=temp;
            ni=i;
        }
    }

    for(i=0;i<n;i++)
    printf("%d %d\n",mi,i);
    for(i=0;i<m;i++)
    if(i!=mi) priintf("%d %d\n",i,ni);    
    
    /*for(i=0;i<n;i++)
    {
        printf("\n0 %d",i);
        arr[i]=arrm[0]+arrn[i];
    }        
    
    for(j=1;j<m;j++)
    {
        for(i=0;i<n;i++)
        {
            temp=arrm[j]+arrn[i];
            flag=0;
            for(t=0;t<k;t++)
            {
                if(temp==arr[t]) flag=1;
            }
            if(flag==0) 
            {
                arr[(int)k]=temp;
                printf("\n%d %d",j,i);
                k++;
                if(k==m+n-1) return 0;
                
            }
        }
    }*/
    
    
	return 0;
}

