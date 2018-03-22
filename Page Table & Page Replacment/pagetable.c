/*
	Page Table
*/
#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"

struct page{
	int page_no;
	int frame;
};
int main()
{
	int size_logical_address,size_physical_address,i,size_of_page,j;
	printf("Enter size of logical address space: ");
	scanf("%d",&size_logical_address);
	printf("Enter size of physical address space: ");
	scanf("%d",&size_physical_address);
	printf("Enter size of page: ");
	scanf("%d",&size_of_page);

	int number_of_frames = size_physical_address/size_of_page;
	int number_of_pages = size_logical_address/size_of_page;

	struct page pageTable[number_of_pages];
	printf("Enter page table: \n");
	for(i=0;i<number_of_pages;i++)
	{
		pageTable[i].frame = -1;
	}
	for(i=0;i<number_of_pages;i++)
	{
		int frame;
		bool replica = false;
		pageTable[i].page_no = i;
		printf("Enter frame for %d page number(-1 if frame doesn't exist): ",i);
		scanf("%d",&frame);
		for(j=0;j<number_of_pages;j++)
		{
			if(frame!= -1 && pageTable[j].frame == frame)
			{
				replica = true;
				printf("Frame number already stored\n");
			}
		}
		if(frame > number_of_frames)
		{
			replica = true;
			printf("Cannot exceed frame size\n");
		}
		if(replica == false)
		{
			pageTable[i].frame = frame;
		}
	}
	int logical_address;
	printf("Enter -1 to exit\n");
	while(1)
	{
		printf("Enter logical address: ");
		scanf("%d",&logical_address);
		if(logical_address == -1)
			return 0;
		
		int page_no = logical_address/size_of_page;
		int offset = logical_address%size_of_page;
		if(pageTable[page_no].frame == -1)
		{
			printf("No such logical address exist\n");
		}
		else
		{
			printf("Page no: %d \nOffset: %d\nFrame no: %d\nPhysical address: %d\n",page_no, offset, pageTable[page_no].frame,pageTable[page_no].frame*size_of_page + offset );
		}
	}
}
