#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>

int sumap=0;
int *suma;

#define ITER	1000
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
    extern int sumap;
    extern int *suma;
    suma =malloc(NCON*sizeof(int));
    for(int i=0;i<NCON;i++){
    	suma[i]=0;
    }
    double *r_valuep,*r_valuec;
    srand(time(NULL));
    void* Productor();
    void* Consumidor(void*);

    //inicializar
	sem_init (&mutex,0,1);


    //Hilos
	pthread_create(&prod, NULL,(void*) Productor,(void*) NULL);

    for(int i =0;i<NCON;i++){
    pthread_create(&con[i], NULL,(void*) Consumidor,(void*) &i);
	}

    // Wait 
	pthread_join(prod, (void **) &r_valuep);

	printf("Suma valores productor (Hilo :%lu) : %i\n",prod,sumap);

	for (int i = 0; i < NCON; i++) {
	pthread_join(con[i], (void **) &r_valuec);
			printf("La suma es(Hilo :%lu) : %i\n",con[i],suma[i]);
    }

    return 0;
    free(suma);
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

void* Consumidor(void* p){
	int dato;
	int *i=(int*)p;
	extern sem_t mutex;
	extern int *suma;
	extern int buffer[NBUFF];
	sem_wait(&mutex);
	for(int j=0;j<NBUFF;j++){
		dato=buffer[j];
		suma[*i]=suma[*i]+dato;
	}
	sem_post(&mutex);
}