#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>

double counter = 0;
int suma = 0;

#define ITER	1000
#define NHILOS	2
#define NBUFF 50
int buffer[NBUFF];
sem_t empty,full,mutex;

int producirDato();
int sacarDato();
void consumirDato();
 
int main()
{
    pthread_t hilos[NHILOS];
    int status, i, v[NHILOS];
    extern double counter;
    extern sem_t empty,full,mutex;
    double *r_value;
    srand(time(NULL));
    void* Productor();
    void* Consumidor();

    //inicializar
    sem_init (&empty,0,NBUFF);
	sem_init (&full,0,0);
	sem_init (&mutex,0,1);


    //Hilos
	
	pthread_create(&hilos[0], NULL, Productor,(void*) NULL);
    usleep(100000);
    pthread_create(&hilos[1], NULL, Consumidor,(void*) NULL);



    // Wait 
    for (i = 0; i < NHILOS; i++) {
	pthread_join(hilos[i], (void **) &r_value);
	printf("Value returned by %lu thread: %lf\n", hilos[i], *r_value);
    }

    return 0;

}

void* Productor(){
	int dato;
	extern sem_t empty,full,mutex;

	for(int j=0;j<NBUFF;j++){
		dato=producirDato();
		sem_wait(&empty);
		sem_wait(&mutex);
		buffer[j]=dato;
		sem_post(&mutex);
		sem_post(&full);

	}
}

void* Consumidor(){
	int dato;
	extern sem_t empty,full,mutex;

	for(int j=0;j<NBUFF;j++){
		sem_wait(&full);
		sem_wait(&mutex);
		dato=sacarDato(j);
		sem_post(&mutex);
		sem_post(&empty);
		consumirDato(dato);
	}
}

int producirDato(){
	return (rand()%1000);
}

int sacarDato(int j){
	return(buffer[j]);
}
void consumirDato(int dato){
	extern int suma;
	suma=suma+dato;
}