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
sem_t mutex;
 
int main()
{
	int NCON;
	printf("Introduzca el numero de hilos consumidores : ");
	scanf("%i",&NCON);
    pthread_t con[NCON],prod;
    extern sem_t mutex;
    extern int sumap,suma;
    double *r_valuep,*r_valuec;
    srand(time(NULL));
    void* Productor();
    void* Consumidor();

    //inicializar
	sem_init (&mutex,0,1);


    //Hilos
	pthread_create(&prod, NULL,(void*) Productor,(void*) NULL);

    for(int i =0;i<NCON;i++){
    pthread_create(&con[i], NULL,(void*) Consumidor,(void*) NULL);
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
	extern sem_t mutex;
	extern int buffer[NBUFF];
	extern int sumap;

	for(int j=0;j<NBUFF;j++){
		dato=(rand()%1000);
		sem_wait(&mutex);
		buffer[j]=dato;
		sem_post(&mutex);
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
		sem_wait(&mutex);
		dato=buffer[j];
		sem_post(&mutex);
		suma=suma+dato;
	}

	pthread_exit((void*)NULL);
}