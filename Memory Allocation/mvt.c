#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
struct process
{
	int id;
	int memory_required;
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

				if(free_memory<memory_required)
				{
					printf("Not enough memory for the process\n");
				}
				else
				{
					proc[i].id = i;
					proc[i].memory_required = memory_required;
					proc[i].removed = false;
					free_memory-=memory_required;
					printf("Process allocated\n");
					i++;
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
					free_memory+=memory_to_remove;
					proc[process_id].removed = true;
				}
			break;
			case 3:
				return 0;
			break;
		}
	}
}