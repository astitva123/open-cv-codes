#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int t,i,n,a,b,flag=0,j,count=0;
    int r;
    
    scanf("%d",&t);
    for(i=0;i<t;i++)
    {
        scanf("%d %d %d",&n,&a,&b);
       // printf("scan successful!");
       //printf("%d--%d--%d",n,a,b);

        
        //printf("\n allocation successful\n");
        int q = 0,w = 0,e = 0;
        for(j=0;j<n;j++)
        {
            scanf("%d",&r);
            if(r%a == 0) q++;
            if(r%b == 0) e++;
            if(r%a == 0 && r%b == 0 ){
              q--;e--;w++;
            }
          //  printf("\nscan in array successful\n");
        }
        /*count=0;
        while(1)
        {   

          //printf("\nwelcome to the game\n");
            if(flag==0)
            {
            //  printf("bob\n");
                for(j=0;j<n;j++)
                {
                   if(count==0)
                   {
                       if(r[j]>0&&r[j]%a==0&&r[j]%b==0)
                       {
                           r[j]=0;
                           flag=1;
                       }
                   }
                   else
                   {
                       if(r[j]>0&&r[j]%a==0)
                       {
                           r[j]=0;
                           flag=1;
                           break;

                       }
        
                  }
              }
            }
            
             if(flag==0&&count==1)
            {
                printf("ALICE");
                break;
            }

            if(flag==1&&count==1)
            {
              //printf("alice\n");
               for(j=0;j<n;j++)
               {
                   if(r[j]>0&&r[j]%b==0)
                   {
                       r[j]=0;
                       flag=0;
                       break;
                   }
               }
            }

            count=1;

            if(flag==1)
            {
                printf("BOB");
                break;
            }
        */

            if(q>e) {
              printf("BOB\n");
              continue;
            }
            if(q<e) {
              printf("ALICE\n");
              continue;
            }
            if(w) printf("BOB\n");
            else{
              printf("ALICE\n");
            }
        }


    return 0;

      
    }

