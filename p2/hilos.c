#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

double counter = 0;
typedef int bool;
#define true 1
#define false 0

#define ITER	1000
#define NHILOS	4

bool eligiendo[NHILOS]={false,false,false,false};
int numero[NHILOS]={0,0,0,0};


int main()
{
    pthread_t hilos[NHILOS];
    int status, i, v[NHILOS];
    extern double counter;
    void *adder(void *);
    double *r_value;

    // Create NHILOS threads
    for (i = 0; i < NHILOS; i++) {
	v[i] = i;
	//usleep(100000);
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
    extern bool eligiendo[NHILOS];
    extern int numero[NHILOS];
    int *id, i;
    int *k=(int*)p;
	id = (int *) p;



	for(int i =0;i<NHILOS;i++){
		eligiendo[i]= true;
		numero[i]=maxNumero(numero)+1;
		eligiendo[i]= false;

		for(int j=0;j<NHILOS;j++){
			while(eligiendo[j]);
			while ((numero[j] != 0) && (numero[j], j) < (numero[i], i));
		}


	//Seccion Critica

    	for (i = 0; i < ITER; i++) {
		l = counter;
		fprintf(stdout, "Hilo %d: %f\n", *id, counter);
		l++;
		counter = l;
    	}

    //Fin seccion critica

    	numero[*k]=0;

    	to_return = malloc(sizeof(double));

    	*to_return = counter;

    	pthread_exit((void *) to_return);

    }



    /*to_return = malloc(sizeof(double));

    *to_return = counter;

    pthread_exit((void *) to_return);*/
}
