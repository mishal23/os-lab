#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "stdbool.h"


int main()
{
	int i,j;
	int no_of_processes,no_of_resources;
	printf("Enter number of processes: ");
	scanf("%d",&no_of_processes);
	printf("Enter number of resources: ");
	scanf("%d",&no_of_resources);

	int allocation[no_of_processes][no_of_resources],maximum[no_of_processes][no_of_resources];
	int available[no_of_resources],need[no_of_processes][no_of_resources];


	printf("Enter allocation matrix\n");
	for(i=0;i<no_of_processes;i++)
	{
		for(j=0;j<no_of_resources;j++)
		{
			scanf("%d",&allocation[i][j]);
		}
	}
	printf("Enter maximum matrix\n");
	for(i=0;i<no_of_processes;i++)
	{
		for(j=0;j<no_of_resources;j++)
		{
			scanf("%d",&maximum[i][j]);
		}
	}
	printf("Enter number of available resources: ");
	int work[no_of_resources];
	bool finish[no_of_processes];
	for(i=0;i<no_of_resources;i++)
	{
		scanf("%d",&available[i]);
		work[i]=available[i];
	}
	for(i=0;i<no_of_processes;i++)
	{
		for(j=0;j<no_of_resources;j++)
		{
			need[i][j]=maximum[i][j]-allocation[i][j];
		}
	}
	
	// Safety Algorithm
	for(i=0;i<no_of_processes;i++)
	{
		finish[i]=false;
	}
	int processes[no_of_processes],k=0;
	while(1)
	{
		bool flag = false;
		
		for(i=0;i<no_of_processes;i++)
		{
			bool enter = true;
			if(finish[i]==false)
			{
				for(j=0;j<no_of_resources;j++)
				{
					if(need[i][j]>work[j])
						enter = false;
				}
				if(enter == true)
				{
					flag = true;
					processes[k]=i;
					k++;
					break;
				}
			}
		}
		if(flag==true)
		{
			for(j=0;j<no_of_resources;j++)
			{
				work[j]+=allocation[i][j];
			}
			finish[i]=true;
		}
		else
			break;
	}
	int processes_finished=0;
	for(i=0;i<no_of_processes;i++)
	{
		if(finish[i]==true)
		{
			processes_finished++;
		}
	}
	if(processes_finished==no_of_processes)
	{
		printf("Safe sequence: ");
		for(i=0;i<no_of_processes;i++)
		{
			printf("%d ", processes[i]);
		}
	}
	else
	{
		printf("Unsafe\n");
	}
	printf("\n");
	
	// Resource Request Algorithm
	int request_process_number;
	printf("Enter process number of process requesting: ");
	scanf("%d",&request_process_number);
	int request[no_of_resources];
	printf("Enter requesting resources: ");
	for(i=0;i<no_of_resources;i++)
	{
		scanf("%d",&request[i]);
	}
	for(i=0;i<no_of_resources;i++)
	{
		if(request[i]>need[request_process_number][i] || request[i]>available[i])
		{
			printf("Enough resources not available\n");
			return 0;
		}
	}
	for(i=0;i<no_of_resources;i++)
	{
		available[i]-=request[i];
		allocation[request_process_number][i]+=request[i];
		need[request_process_number][i]-=request[i];
	}

	// RE- Safety Algorithm
	for(i=0;i<no_of_processes;i++)
	{
		finish[i]=false;
	}
	while(1)
	{
		bool flag = false;
		
		for(i=0;i<no_of_processes;i++)
		{
			bool enter = true;
			if(finish[i]==false)
			{
				for(j=0;j<no_of_resources;j++)
				{
					if(need[i][j]>work[j])
						enter = false;
				}
				if(enter == true)
				{
					flag = true;
					processes[k]=i;
					k++;
					break;
				}
			}
		}
		if(flag==true)
		{
			for(j=0;j<no_of_resources;j++)
			{
				work[j]+=allocation[i][j];
			}
			finish[i]=true;
		}
		else
			break;
	}
	processes_finished=0;
	for(i=0;i<no_of_processes;i++)
	{
		if(finish[i]==true)
		{
			processes_finished++;
		}
	}
	if(processes_finished==no_of_processes)
	{
		printf("Safe sequence: ");
		for(i=0;i<no_of_processes;i++)
		{
			printf("%d ", processes[i]);
		}
	}
	else
	{
		printf("Unsafe\n");
	}
}