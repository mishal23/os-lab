#include "stdio.h"
#include "stdlib.h"
#include "sys/wait.h"
#include "unistd.h"
#include "pthread.h"

pthread_t philosophers[50];
pthread_mutex_t chopsticks[50];

int n;

void *thinkEatRepeat(int i)
{
	printf("%d Thinking ..\n",i+1 );

	pthread_mutex_lock(&chopsticks[i]);
	pthread_mutex_lock(&chopsticks[(i+1)%n]);

	printf("%d eating...\n",i+1 );
	sleep(1);
	
	if(i!=n){	
		pthread_mutex_unlock(&chopsticks[i]);
		pthread_mutex_unlock(&chopsticks[(i+1)%n]);		
	}
	else{	//It handles the case when all philosphers pick the chopstick to their right which will result in a deadlock
		pthread_mutex_unlock(&chopsticks[i]);
		pthread_mutex_unlock(&chopsticks[(i-1)%n]);		
	}
	printf("\t%d Finished eating\n", i+1);

	return NULL;
}

int main()
{
	printf("Enter number of philosophers: ");
	scanf("%d",&n);
	int i;
	for(i=0;i<n;i++)
	{
		pthread_mutex_init(&chopsticks[i],NULL);
	}
	for(i=0;i<n;i++)
	{
		pthread_create(&philosophers[i],NULL,thinkEatRepeat,i);
	}
	for(i=0;i<n;i++)
	{
		pthread_join(philosophers[i],NULL);
	}
	/*for(i=0;i<n;i++)
	{
		pthread_mutex_destroy(&chopsticks[i]);
	}*/
}
