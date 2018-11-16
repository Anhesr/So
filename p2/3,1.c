#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>

int sumap=0;
int suma=0;

#define ITER	1000
#define NHILOS	2
#define NBUFF 5
int buffer[NBUFF];
sem_t empty,full,mutex;

int main()
{
    pthread_t con,prod;
    extern sem_t empty,full,mutex;
    extern int sumap,suma;
    double *r_valuep,*r_valuec;
    srand(time(NULL));
    void* Productor();
    void* Consumidor();

    //inicializar
    sem_init (&empty,0,1);
	sem_init (&full,0,0);
	sem_init (&mutex,0,NBUFF);


    //Hilos
	pthread_create(&prod, NULL,(void*) Productor,(void*) NULL);
    pthread_create(&con, NULL,(void*) Consumidor,(void*) NULL);


    // Wait 
	pthread_join(prod, (void **) &r_valuep);
	pthread_join(con, (void **) &r_valuec);

	printf("Suma valores productor (Hilo :%lu) : %i\n",prod,sumap);
	printf("Suma valores consumidor(Hilo :%lu) : %i\n",con,suma);

    return 0;

}

void* Productor(){
	int dato;
	extern sem_t empty,full,mutex;
	extern int buffer[NBUFF];
	extern int sumap;

	for(int j=0;j<NBUFF;j++){
		dato=(rand()%1000);
		sem_wait(&empty);
		sem_wait(&mutex);
		buffer[j]=dato;
		sem_post(&mutex);
		sem_post(&full);
		sumap=sumap+dato;

	}

	pthread_exit((void*)NULL);
}

void* Consumidor(){
	int dato;
	extern sem_t empty,full,mutex;
	extern int buffer[NBUFF];

	for(int j=0;j<NBUFF;j++){
		sem_wait(&full);
		sem_wait(&mutex);
		dato=buffer[j];
		sem_post(&mutex);
		sem_post(&empty);
		suma=suma+dato;
	}

	pthread_exit((void*)NULL);
}

