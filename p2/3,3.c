#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>

int sumap=0;
int suma=0;
sem_t empty,full,mutex;

#define ITER	1000
#define NHILOS	2
#define NBUFF 5
int buffer[NBUFF];
 
int main()
{
	int NCON;
	printf("Introduzca el numero de hilos consumidores : ");
	scanf("%i",&NCON);
    pthread_t con[NCON],prod;
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
	usleep(1000);

    for(int i =0;i<NCON;i++){
    pthread_create(&con[i], NULL,(void*) Consumidor,(void*) NULL);
    usleep(1000);
	}

    // Wait 
	pthread_join(prod, (void **) &r_valuep);

	printf("Suma valores productor (Hilo :%lu) : %i\n",prod,sumap);

	for (int i = 0; i < NCON; i++) {
	pthread_join(con[i], (void **) &r_valuec);
		if(i==NCON-1){
			printf("La suma final de los hilos consumidores es(Hilo :%lu) : %i\n",con[i],suma);
		}
    }

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
	extern int suma;
	extern int buffer[NBUFF];
	for(int j=0;j<NBUFF;j++){
		sem_wait(&full);
		sem_wait(&mutex);
		dato=buffer[j];
		sem_post(&mutex);
		sem_post(&empty);
		sem_post(&full);
		suma=suma+dato;
	}

	pthread_exit((void*)NULL);
}