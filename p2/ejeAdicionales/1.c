#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int v[3],resul[3];
int m[3][3];

typedef int bool;
#define true 1
#define false 0

bool eligiendo[3]={false,false,false};
int numero[3]={0,0,0};

int maxNumero(int* v);

int main(){
	pthread_t hilos[3];
	srand(time(NULL));
	double* r_value;	
	void *mul(void*);

	printf("Vector:\n");
	for(int i=0;i<3;i++){
		resul[i]=0;
		v[i]=(rand()%10);
		printf("(%i)\t",v[i]);
	}
	printf("\n");
	printf("Matriz:\n");
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			m[i][j]=(rand()%10);
			printf("(%i)\t",m[i][j]);
		}
		printf("\n");
	}

	for(int i=0;i<3;i++){
		pthread_create(&hilos[i],NULL,mul,(void*) &i);
		usleep(100000);
	}

	for(int i=0;i<3;i++){
		pthread_join(hilos[i], (void **) &r_value);
		printf("hilo %lu retorno el valor %i de la posicion %i del vector\n", hilos[i],resul[i],i+1);
	}

}

int maxNumero(int *v){
	for(int i=0;i<4;i++){
		if((v[i]>v[0])&&(v[i]>v[1])&&(v[i]>v[2])&&(v[i]>v[3])){return v[i];}
	}
}

void *mul(void* p){
	extern int v[3],resul[3];
	extern int m[3][3];
	extern bool eligiendo[3];
    extern int numero[3];
	int *i=(int*)p;

	for(int k =0;k<3;k++){
		eligiendo[*i]= true;
		numero[*i]=maxNumero(numero)+1;
		eligiendo[*i]= false;

		for(int j=0;j<3;j++){
			while(eligiendo[j]);
			while ((numero[j] != 0) && ((numero[j]<numero[*i]) || ((numero[j]==numero[*i])&&(j<*i))));
		}
		//SECCION CRITICA
		for(int j=0;j<3;j++){
			resul[*i]=resul[*i]+(m[*i][j]*v[j]);
		}
		//fin 
		numero[*i]=0;
		pthread_exit(NULL);
	}

}