#include "stdio.h"
#include "stdlib.h"
struct process
{
	int pid;
	int at;
	int bt;
	int wt;
	int tat;
	int rt;
	int ct;
	int priority;
};
int main()
{
	int n,i,j,tq;
	printf("Enter number of processes: ");
	scanf("%d",&n);
	struct process proc[n];
	int burst[n];
	for(i=0;i<n;i++)
	{
		printf("Enter arrival time for process%d: ",i+1 );
		scanf("%d",&proc[i].at);
		printf("Enter burst time for process%d: ",i+1 );
		scanf("%d",&proc[i].bt);
		printf("Enter priority for process%d: ",i+1 );
		scanf("%d",&proc[i].priority);
		proc[i].pid= i+1;
		proc[i].rt = proc[i].bt;
		burst[i]=proc[i].bt;
	}
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(proc[j].at > proc[j+1].at)
			{
				struct process temp = proc[j];
				proc[j] = proc[j+1];
				proc[j+1] = temp;
			}
		}
	}
	printf("Enter time quantum: ");
	scanf("%d",&tq);
	int avgt=0,avgw=0;
	int tim=-1,tot=n,mini=1e9,pos=-1;
	while(tot)
	{
		tim++;
		mini =1e9;
		pos=-1;

		//find minimum priority process at time=tim
		for(int i=0;i<n;i++)
		{
			if(mini>proc[i].priority && burst[i] && tim>=proc[i].at)
			{
				pos=i;
				mini=proc[i].priority;
			}
		}

		// if no such process found
		if(pos==-1)
			continue;

		burst[pos]--;
		for(int i=0;i<n;i++)
		{
			if(i!=pos && burst[i] && tim>=proc[i].at)
			{
				proc[i].wt++;
			}
		}

		if(burst[pos]==0)
		{
			tot--;
			proc[pos].tat = tim - proc[pos].at +1;

			avgt+=proc[pos].tat;
			avgw+=proc[pos].wt;
		}
	}
	for(i=0;i<n;i++)
	{
		printf("%d %d %d %d %d %d\n",proc[i].pid,proc[i].priority,proc[i].at,proc[i].bt,proc[i].bt,proc[i].wt );
	}
}