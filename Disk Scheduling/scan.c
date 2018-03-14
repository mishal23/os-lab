/*
	Disk Scheduling
	Scan
*/
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

struct request
{
	int request_track_number;
	bool visited;
};

int main()
{
	int i,no_of_requests,initial_head,limit,j,choice,previous_head;
	printf("Enter the number of requests: ");
	scanf("%d",&no_of_requests);
	struct request req[no_of_requests];
	printf("Enter the requests: ");
	for (i = 0; i < no_of_requests; ++i)
	{
		scanf("%d",&req[i].request_track_number);
		req[i].visited = false;
	}
	printf("Enter initial position of R/W head: ");
	scanf("%d",&initial_head);

	printf("Enter the previous position of R/W head: ");
	scanf("%d",&previous_head);

	printf("Enter the cylinder size: ");
	scanf("%d",&limit);

	if(previous_head - initial_head > 0 )
	{
		choice = 2;
	}
	else
		choice = 1;
	//scanf("%d",&choice);
	int seek_time=0;
	printf("%d -> ",initial_head );
	if(choice == 1)
	{
		for(i=initial_head;i<limit;i++)
		{
			for(j=0;j<no_of_requests;j++)
			{
				if(req[j].request_track_number == i && req[j].visited == false)
				{
					printf("%d -> ", req[j].request_track_number);
					req[j].visited = true;
					seek_time += abs(req[j].request_track_number - initial_head);
					initial_head = req[j].request_track_number;
				}
			}
		}
		printf("%d -> ", limit-1);
		seek_time += abs(limit-1 - initial_head);
		initial_head = limit-1;
		for(i=initial_head;i>=0;i--)
		{
			for(j=0;j<no_of_requests;j++)
			{
				if(req[j].request_track_number == i && req[j].visited == false)
				{
					printf("%d -> ", req[j].request_track_number);
					req[j].visited = true;
					seek_time += abs(req[j].request_track_number - initial_head);
					initial_head = req[j].request_track_number;
				}
			}
		}
		seek_time += abs(initial_head - 0);
		printf("0 \n");
	}
	else if(choice == 2)
	{
		for(i=initial_head;i>=0;i--)
		{
			for(j=0;j<no_of_requests;j++)
			{
				if(req[j].request_track_number == i && req[j].visited == false)
				{
					printf("%d -> ", req[j].request_track_number);
					req[j].visited = true;
					seek_time += abs(req[j].request_track_number - initial_head);
					initial_head = req[j].request_track_number;
				}
			}
		}
		printf("%d -> ", 0);
		seek_time += abs(0 - initial_head);
		initial_head = 0;
		for(i=initial_head;i<limit;i++)
		{
			for(j=0;j<no_of_requests;j++)
			{
				if(req[j].request_track_number == i && req[j].visited == false)
				{
					printf("%d -> ", req[j].request_track_number);
					req[j].visited = true;
					seek_time += abs(req[j].request_track_number - initial_head);
					initial_head = req[j].request_track_number;
				}
			}
		}
		seek_time += abs(limit-1 - initial_head );
		printf("%d \n", limit-1);
		
	}
	printf("Seek Time: %d\n", seek_time);
}