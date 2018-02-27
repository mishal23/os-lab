#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int need[100][100],allot[100][100],max[100][100],available[100];
bool isFinished[100];
int sequence[100];

void isSafe(int N,int M)
{
        int i,j,work[100],count=0;
        for(i=0;i<M;i++)
            work[i]=available[i];
        for(i=0;i<100;i++)
            isFinished[i]=false;
        while(count<N)
        {
                bool canAllot=false;
                for(i=0;i<N;i++)
                {
                   if(isFinished[i]==false)
                   {

                        for(j=0;j<M;j++)
                        {
                            if(work[j]<need[i][j])
                            {
                                break;
                            }
                        }
                        if(j==M)
                        {
                            for(j=0;j<M;j++)
                            {
                                work[j]+=allot[i][j];
                            }

                            sequence[count++]=i;
                            isFinished[i]=true;
                            canAllot=true;
                        }
                   }
                }
                if(canAllot==false)
                {
                    printf("System Is  not safe\n");
                    return ;
                }
        }

        printf("System is in safe state\n");

        printf("Safe sequence :");
        for(i=0;i<N;i++)
            printf("%d ",sequence[i]);
        printf("\n");
}

int main()
{
        int i,j,N,M;
        printf("Enter the number of process and resources :");
        scanf("%d %d",&N,&M);

        printf("Enter the available resources :\n");

        for(i=0;i<M;i++)
            scanf("%d",&available[i]);

        printf("Enter the Allocation Matrix :\n");

        for(i=0;i<N;i++)
            for(j=0;j<M;j++)
                scanf("%d",&allot[i][j]);

        printf("Enter the matrix for maximum demand of each process :\n");

        for(i=0;i<N;i++)
            for(j=0;j<M;j++)
                scanf("%d",&max[i][j]);

        //calculation of need matrix
        for(i=0;i<N;i++)
            for(j=0;j<M;j++)
                need[i][j]=max[i][j]-allot[i][j];

        isSafe(N,M);

        int indx,arr[100];
        printf("Enter the process no for resource request :");
        scanf("%d",&indx);

        printf("Enter the requested instances of Each :");
        for(i=0;i<M;i++)
            scanf("%d",&arr[i]);

        for(i=0;i<M;i++)
        {
            if( need[indx][i]<arr[i] || arr[i]>available[i] )
            {
                printf("Cannot request\n");
                break;
            }
        }

        if(i==M)
        {
            for(i=0;i<M;i++)
            {
                allot[indx][i]+=arr[i];
                available[i]-=arr[i];
                need[indx][i]-=arr[i];
            }

            isSafe(N,M);
        }

}