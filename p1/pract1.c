//Angel Francisco Santos Ramirez GG2 Ing Informática
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <math.h>
#include <time.h>

#define CHILDREN	3
#define Ok	5


void opvector1(int *v);
void opvector2(int *v);
void opvector3(int *v);
void inicializa(int *v);

int main(){
	
	srand(time(NULL));
	int i, shmid, status;
    key_t key;
    struct shmid_ds buf;
    int *v;


    key = ftok("pract1.c", Ok);

    if ((shmid = shmget(key, (sizeof(int)*100), IPC_CREAT | 0777)) == -1)
	exit(1);

	v=(int *) shmat(shmid, NULL, 0);
	
	inicializa(v);
	

	if (!fork()) {
		opvector1(v);
	   	exit(0);
	}

	if (!fork()) {
		opvector2(v);
	   	exit(0);
	}


	if (!fork()) {
		opvector3(v);
	   	exit(0);
	}

	for (i = 0; i < CHILDREN; i++) {
	pid_t pid = wait(&status);
	printf("\nChild %d finished with status %d\n", pid, WEXITSTATUS(status));
    }

    shmdt(v);
    shmctl(shmid, IPC_RMID, &buf);
    return 0;	

}

void opvector1(int *v){
	int in;
	int ele;
	for (int i =0;i<10;i++){
		
	printf("Introduce la posicion del vector\n");
	scanf("%i", &in );

	printf("Introduce el elemento a insertar en el vector\n");
	scanf("%i", &ele );
	

	v[in]=ele;
	printf("Elemento insertado\n");	
	}
	exit(Ok);
	
}

void opvector2(int *v){
	int in;
	printf("v[1]= ",v[1]);
	for (int i =0;i<100;i++){
		in = (rand()%100);
		v[in] = (rand());
		//printf("El elemento %i se inserto en la posicion %i\n", v[in] , in);
		sleep(1);

	}
	exit(Ok);
}

void opvector3(int *v){
	int suma;
	for (int i =0;i<5;i++){
		suma=0;
		for(int j=0;j<100;j++){
			suma=suma+v[j];
		}
		printf("La suma es %i\n",suma );
		//printf("v[1]= %i\n",v[1]);
		sleep (30);
	}
	exit(Ok);
}

void inicializa(int *v){

	for(int i=0;i<100;i++){
		v[i]=(rand());
		//printf("v[i]= %i\n",v[i]);
	}

}
