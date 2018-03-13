/*
	Worst Fit
	Multiprogramming with Fixed Number of Tasks
*/
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

struct process
{
	int id;
	int memory_required;
	int allocated_partition;
	int external_fragment;
	bool allocated;
};
struct partition
{
	int id;
	int size;
	int internal_fragment;
	bool alloted;
};
int main()
{
	int memory,no_of_partitions,no_of_processes,i,j,sum=0;
	printf("Enter total memory: ");
	scanf("%d",&memory);
	printf("Enter number of partitions: ");
	scanf("%d",&no_of_partitions);
	struct partition parti[no_of_partitions];
	for(i=0;i<no_of_partitions;i++)
	{
		printf("Enter memory for partition%d: ",i+1);
		scanf("%d",&parti[i].size);
		parti[i].id = i+1;
		parti[i].alloted=false;

		sum+=parti[i].size;
	}
	if(sum < memory)
	{
		no_of_partitions++;
		parti[i].size = memory - sum;
		parti[i].id = i+1;
		parti[i].alloted=false;
		printf("Size of partition%d: %d\n",i+1,parti[i].size );
	}
	for(i=0;i<no_of_partitions-1;i++)
	{
		for(j=0;j<no_of_partitions-1-i;j++)
		{
			if(parti[j].size<parti[j+1].size)
			{
				struct partition temp = parti[j];
				parti[j] = parti[j+1];
				parti[j+1] = temp;
			}
		}
	}
	/*for(i=0;i<no_of_partitions;i++)
	{
		printf("%d\n",parti[i].size );
	}*/
	int total_internal_fragment=0, total_external_fragment=0;
	printf("Enter number of processes: ");
	scanf("%d",&no_of_processes);
	struct process proc[no_of_processes];
	for (i = 0; i < no_of_processes; ++i)
	{
		printf("Enter memory required for process%d: ",i+1 );
		scanf("%d",&proc[i].memory_required);
		proc[i].id = i+1;
		proc[i].external_fragment=0;
		proc[i].allocated = false;
		for(j=0;j<no_of_partitions;j++)
		{
			if(proc[i].memory_required<=parti[j].size && !parti[j].alloted)
			{
				proc[i].allocated = true;
				proc[i].allocated_partition = parti[j].id;
				parti[j].internal_fragment = parti[j].size - proc[i].memory_required;
				total_internal_fragment+=parti[j].internal_fragment;
				parti[j].alloted=true;
				break;
			}
			/*else if(proc[i].memory_required<=parti[j+1].size && !parti[j+1].alloted)
			{
				proc[i].allocated = true;
				proc[i].allocated_partition = parti[j+1].id;
				parti[j+1].internal_fragment = parti[j+1].size - proc[i].memory_required;
				total_internal_fragment+=parti[j+1].internal_fragment;
				parti[j+1].alloted=true;
				break;
			}
			else
			{
				proc[i].allocated = false;
			}*/
		}
		for(j=0;j<no_of_partitions;j++)
		{
			if(parti[j].alloted==false)
			{
				proc[i].external_fragment+=parti[j].size;
			}
		}
	}
	for(j=0;j<no_of_partitions;j++)
	{
		if(!parti[j].alloted)
		{
			total_external_fragment+=parti[j].size;
			parti[j].internal_fragment = -1;
		}
	}
	printf("ProcessID\tMemory required\tAllocated\tAllocated Partition\n");
	for(i=0;i<no_of_processes;i++)
	{
		if(proc[i].allocated)
		{
			printf("%d\t\t%d\t\t\tYES\t%d\t\n",proc[i].id, proc[i].memory_required,  proc[i].allocated_partition);
		}
		else
		{
			printf("%d\t\t%d\t\t\tNO\t%d\n",proc[i].id, proc[i].memory_required, proc[i].external_fragment);
		}
	}
	printf("\n");
	printf("Internal Fragmentation\n");
	for(i=0;i<no_of_partitions;i++)
	{
		if(parti[i].internal_fragment==-1)
		{
			printf("%d ---\n",parti[i].id);
		}
		else
			printf("%d %d\n",parti[i].id,parti[i].internal_fragment );
	}
	printf("Total internal Fragmentation: %d\nTotal external Fragmentation: %d\n",total_internal_fragment, total_external_fragment);
}