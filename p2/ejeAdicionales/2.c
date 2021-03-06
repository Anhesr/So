#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

double counter = 0;
typedef int bool;
int NHILOS;
int ITER;
#define true 1
#define false 0

//#define ITER	1000
//#define NHILOS	4

bool eligiendo[]={false,false,false,false};
int numero[NHILOS]={0,0,0,0};


int main()
{
    pthread_t hilos[NHILOS];
    int status, i, v[NHILOS];
    extern double counter;
    void *adder(void *);
    double *r_value;
    extern int NHILOS;

    printf("introduzca el numero de hilos");
    scanf("%i",&NHILOS);
    extern int ITER=NHILOS*100;

    // Create NHILOS threads
    for (i = 0; i < NHILOS; i++) {
	v[i] = i;
	if ((status = pthread_create(&hilos[i], NULL, adder, (void *) &v[i])))
	    exit(status);
    }

    // Wait threads
    for (i = 0; i < NHILOS; i++) {
	pthread_join(hilos[i], (void **) &r_value);
	printf("Value returned by %lu thread: %lf\n", hilos[i], *r_value);
    }

    // Final result
    fprintf(stdout, "%f\n", counter);

    return 0;
}


int maxNumero(int *v){
	for(int i=0;i<4;i++){
		if((v[i]>v[0])&&(v[i]>v[1])&&(v[i]>v[2])&&(v[i]>v[3])){return v[i];}
	}
}


void *adder(void *p)
{
    double l, *to_return;
    extern double counter;
    extern int NHILOS;
    extern int ITER=NHILOS*100;
    extern bool eligiendo[NHILOS];
    extern int numero[NHILOS];
    int *id, i;
	id = (int *) p;



	for(int k =0;k<ITER;k++){
		eligiendo[*id]= true;
		numero[*id]=maxNumero(numero)+1;
		eligiendo[*id]= false;

		for(int j=0;j<NHILOS;j++){
			while(eligiendo[j]);
			while ((numero[j] != 0) && ((numero[j]<numero[*id]) || ((numero[j]==numero[*id])&&(j<*id))));
		}


	//Seccion Critica

    	for (i = 0; i < ITER; i++) {
		l = counter;
		fprintf(stdout, "Hilo %d: %f\n", *id, counter);
		l++;
		counter = l;
    	}

    //Fin seccion critica

    	numero[*id]=0;

    	to_return = malloc(sizeof(double));

    	*to_return = counter;

    	pthread_exit((void *) to_return);

    }
}