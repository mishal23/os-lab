/*
	Deallocation
	Multiprogramming with Variable Number of Tasks

	Note: This code isn't correct for all test cases
*/
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
struct process
{
	int id;
	int memory_required;
	int external_fragment;
	int internal_fragment;
	bool removed;
};
int main()
{
	int memory;
	printf("Enter total memory size: ");
	scanf("%d",&memory);
	struct process proc[100];
	int free_memory = memory;
	int i=0;
	int choice,memory_to_remove,memory_required,process_id;
	while(1)
	{
		printf("Enter 1 to enter\nEnter 2 to leave\nEnter 3 exit\n");
		printf("Enter your choice: ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				printf("Enter memory size for process%d: ",i+1);
				scanf("%d",&memory_required);
				int new_internal_space = 0;
					for(int j=0;j<i;j++)
					{
						if(proc[j].removed == true )
						{
							new_internal_space+=proc[j].internal_fragment;
						}
					}

				if(free_memory < memory_required)
				{
					printf("Free Memory: %d\n",free_memory );
					printf("Not enough memory for the process\n");
				}
				else if(new_internal_space > memory_required)
					{
						printf("Process allocated\n" );
						printf("Free memory: %d\n",free_memory + new_internal_space - memory_required );
					}
					else if(free_memory - new_internal_space >= memory_required)
					{
						proc[i].id = i;
						proc[i].memory_required = memory_required;
						proc[i].removed = false;
						free_memory-=memory_required;
						proc[i].internal_fragment = 0;
						proc[i].external_fragment = free_memory;
						printf("Process allocated\n");
						printf("Free memory: %d\n",free_memory );
						i++;
					}
					else
					{
						printf("Process not allocated\n");
						printf("%d %d\n",free_memory, new_internal_space );
					}

			break;
			
			case 2:
				printf("Enter the id of process leaving: ");
				scanf("%d",&process_id);
				if(proc[process_id].removed)
				{
					printf("Process not in memory\n");
				}
				else
				{
					int memory_to_remove = proc[process_id].memory_required;
					proc[process_id].internal_fragment = memory_to_remove;
					free_memory+=memory_to_remove;
					proc[process_id].external_fragment = free_memory;
					proc[process_id].removed = true;
					printf("Free Memory: %d\n",free_memory );
				}
			break;
			case 3:
				return 0;
			break;
		}
	}
}