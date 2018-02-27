#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"
#include "semaphore.h"

#define BUFFER_SIZE 16

sem_t fill;
sem_t empty;

pthread_t producerThread[50], consumerThread[50];
int buffer[BUFFER_SIZE];
int counter;

//pthread_mutex_t mutex;
sem_t mutex;

void init()
{
	sem_init(&mutex,0,1);
	//pthread_mutex_init(&mutex,NULL);
	sem_init(&fill,1,0);
	sem_init(&empty,1,BUFFER_SIZE);
	counter=0;
}

void produce(int item)
{
	buffer[counter++]=item;
}

int consume()
{
	counter--;
	return buffer[counter];
}

void *producer(void *param)
{
	int item;
	item=rand()%5;
	sem_wait(&empty);
	/*printf("sem_wait = %d\n",wait );
	int val;
	printf("emptyb=%d\n", sem_getvalue(&empty,&val));
	printf("%d\n",val );
	printf("emptya=%d\n", sem_getvalue(&empty,&val));
	printf("%d\n",val );*/
	//pthread_mutex_lock(&mutex);
	sem_wait(&mutex);
	printf("Produced item: %d\n", item);
	produce(item);

	//pthread_mutex_unlock(&mutex);
	sem_post(&mutex);
	sem_post(&fill);
}

void *consumer(void *param)
{
	int item;
	sem_wait(&fill);
	//pthread_mutex_lock(&mutex);
	sem_wait(&mutex);
	item =consume();
	printf("Consumed item: %d\n",item );

	sem_post(&mutex);
	//pthread_mutex_unlock(&mutex);
	sem_post(&fill);	
}

int main()
{
	int i,number_of_producers,number_of_consumers;
	init();

	printf("Enter number of producers: ");
	scanf("%d",&number_of_producers);

	printf("Enter number of consumers: ");
	scanf("%d",&number_of_consumers);

	for(i=0;i<number_of_producers;i++)
	{
		pthread_create(&producerThread[i],NULL,producer,NULL);
	}
	for(i=0;i<number_of_consumers;i++)
	{
		pthread_create(&consumerThread[i],NULL,consumer,NULL);
	}
	for(i=0;i<number_of_producers;i++)
	{
		pthread_join(producerThread[i],NULL);
	}
	for(i=0;i<number_of_consumers;i++)
	{
		pthread_join(consumerThread[i],NULL);
	}
	return 0;
}