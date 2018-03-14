/*
	Disk Scheduling
	Shortest Seek Time First
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

	int seek_time=0;
	printf("%d -> ",initial_head );
	int n = no_of_requests;
	while(n)
	{
		int min = 1e9;
		int min_track_number, position;
		for(i=0;i<no_of_requests;i++)
		{
			if(abs(initial_head - req[i].request_track_number) < min && req[i].visited == false)
			{
				min = abs(initial_head - req[i].request_track_number);
				min_track_number = req[i].request_track_number;
				position = i;
			}
		}
		initial_head = req[position].request_track_number;
		req[position].visited = true;
		printf("%d ->",min_track_number);
		seek_time += min;
		n--;
	}

	printf("\nSeek Time: %d\n", seek_time);
}