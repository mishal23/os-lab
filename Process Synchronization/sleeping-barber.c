#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "pthread.h"
#include "semaphore.h"
#include "stdbool.h"

sem_t barberReady,accessWRseats,customerReady;
int numberofFreeWRSeats;
int n;
pthread_t customersThread[100];
int no_of_customers;

void *barber(void *params)
{
	int haircuts = no_of_customers-1;
	while(true)
	{
		sem_wait(&customerReady);
		sem_wait(&accessWRseats);
		numberofFreeWRSeats++;
		sem_post(&barberReady);
		no_of_customers--;
		printf("Cutting hair, waiting for next customer\n");
		sem_post(&accessWRseats);
		printf("Barber: , chairs left=%d\n",numberofFreeWRSeats);
	}
	printf("Closing shop\n");

}

void *customer(void *params)
{
	int haircuts=1;
	while(haircuts>0)
	{
		sem_wait(&accessWRseats);
		if(numberofFreeWRSeats>0)
		{
			numberofFreeWRSeats--;
			printf("Customer taking a seat\n");
			sem_post(&customerReady);
			haircuts--;
			sleep(1);
			sem_post(&accessWRseats);
			sem_wait(&barberReady);
			printf("Customer %d getting haircut\n",*(int *)params );
		}
		else
		{
			sem_post(&accessWRseats);
			printf("Customer%d couldn't get a haircut,numberofFreeWRSeats=%d\n",*(int *)params,numberofFreeWRSeats );
		}
	}
}

void init()
{
	sem_init(&barberReady,0,0);
	sem_init(&accessWRseats,0,1);
	sem_init(&customerReady,0,0);
	numberofFreeWRSeats=n;
}

int main()
{
	int i;
	printf("Enter number of waiting room seats: ");
	scanf("%d",&n);
	init();
	printf("Enter number of customers: ");
	scanf("%d",&no_of_customers);
	for(i=0;i<no_of_customers;i++)
	{
		if(i==0)
		{
			pthread_create(&customersThread[i],NULL,barber,&i);	
		}
		else
			pthread_create(&customersThread[i],NULL,customer,&i);
	}
	for(i=0;i<no_of_customers;i++)
	{
		pthread_join(customersThread[i],NULL);
	}
}