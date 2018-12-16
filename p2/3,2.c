#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>

int sumap=0;
int suma=0;
int check=0;
int NCON,NPROD,nbuffer;
sem_t empty,full,mutex,sem1;
void* Productor(void*);
void* Consumidor(void*);
int *buffer;
 
int main()
{
	srand(time(NULL));

	printf("Introduzca el numero de hilos Productores : ");
	scanf("%d",&NPROD);

	printf("Introduzca el numero de hilos consumidores : ");
	scanf("%d",&NCON);

	printf("Introduzca el numero de èlementos del buffer : ");
	scanf("%d",&nbuffer);

	int v1[NPROD];
	int v2[NCON];

    pthread_t con[NCON],prod[NPROD];
    double *r_valuep,*r_valuec;

    buffer=(int*)malloc(nbuffer*sizeof(int));

    //inicializar
    sem_init (&mutex,0,1);
	sem_init (&full,0,0);
	sem_init (&empty,0,nbuffer);
	sem_init (&sem1,0,0);


    //Hilos
	for(int i=0;i<NPROD;i++){
		v1[i]=i;
	pthread_create(&prod[i], NULL,(void*) Productor,(void*) &v1[i]);
	}

    for(int i =0;i<NCON;i++){
    	v2[i]=i;
    pthread_create(&con[i], NULL,(void*) Consumidor,(void*) &v2[i]);	
    }

    // Wait 
    for(int i=0;i< NCON;i++){
	pthread_join(prod[i], NULL);
	}

	for (int i = 0; i < NCON; i++) {
	pthread_join(con[i], NULL);
	}

	printf("Suma valores productores : %i\n",sumap);
    printf("La suma final de los hilos consumidores es : %i\n",suma);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    sem_destroy(&sem1);
	free(buffer);
    return 0;

}

void* Productor(void*p){
	int dato,det,fin,inicio;

	det=*(int*)p;
	inicio = (nbuffer/NPROD)*det;
	if((det+1)==NPROD){
		fin=nbuffer;
	}
	else{
		fin=((nbuffer/NPROD)*(det+1));
	}

	for(int j=inicio ; j<fin ; j++){
		dato=(rand()%1000);
		sem_wait(&empty);
		sem_wait(&mutex);
		buffer[j]=dato;
		check++;
		sem_post(&mutex);
		sem_post(&full);
		sumap=sumap+dato;
	}
	if(check == nbuffer){
		sem_post(&sem1);
	}


	pthread_exit((void*)NULL);
}

void* Consumidor(void*p){
	int dato,det,fin,inicio;
	det=*(int*)p;
	inicio=(nbuffer/NCON)*det;
	if((det+1)==NCON){
		fin=nbuffer;
	}
	else{
		fin=((nbuffer/NCON)*(det+1));
	}
	for(int j=inicio ; j<fin ; j++){
		sem_wait(&sem1);
		sem_wait(&full);
		sem_wait(&mutex);
		dato=buffer[j];
		sem_post(&mutex);
		sem_post(&empty);
		sem_post(&sem1);
		suma=suma+dato;
	}

	pthread_exit((void*)NULL);
}