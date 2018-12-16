#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t mutex;

int *v;
int NVE;

#define ITER 100

int main(){
	int NHI;
	int rnd;
	extern int NVE;
	extern int *v;
	printf("Introduzca el numero de hilos :");
	scanf("%i",&NHI);
	void* randomV(void*);
	srand(time(NULL));

	pthread_t hilos[NHI];
	double *r_value;

	printf("Introduzca el numero de elementos del vector :");
	scanf("%i",&NVE);

	v = malloc(NVE*sizeof(int));

	for(int i =0;i<NVE;i++){
		v[i]=0;
	}

	int aux[NHI];
	sem_init (&mutex,0,1);
	for(int i=0;i<NHI;i++){
		aux[i]=rand()%NVE;
		pthread_create(&hilos[i], NULL, randomV, (void*) &aux[i]);
	}

	for (int i = 0; i < NHI; i++) {
	pthread_join(hilos[i], (void **) &r_value);
    }

    int sum=0;

    for(int i = 0;i<NVE;i++){
		sum=sum+v[i];
	}
	printf("suma vector = %i\n",sum);

    return 0;
}

void * randomV(void * p){
	extern int *v;
	extern sem_t mutex;
	int *l=(int*)p;
	sem_wait(&mutex);
	for(int i=0;i<100;i++){
		v[*l]=v[*l]+1;
	}
	sem_post(&mutex);
	 pthread_exit(NULL);
}
