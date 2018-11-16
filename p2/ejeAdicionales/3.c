#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t mutex;

int v[NVE];

#define ITER 100

int main(){
	int NHI;
	int rnd;
	printf("Introduzca el numero de hilos");
	scanf("%i",&NHI);
	void* random(void*)
	srand(time(NULL));

	pthread_t hilos[NHI];
	double *r_value;

	printf("Introduzca el numero de elementos del vector");
	scanf("%i",&NVE);

	for(int i =0;i<NVE;i++){
		v[i]=0;
	}

	for(int i=0;i<NHI;i++){
		rnd=rand()%100;
		pthread_create(&hilos[i], NULL, random, (void*) &rnd);
	}

}
