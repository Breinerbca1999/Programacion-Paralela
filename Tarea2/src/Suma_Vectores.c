/*
 ============================================================================
 Name        : Tarea2.c
 Author      : breiner
 Version     :
 Copyright   : Your copyright notice
 Description : Compute Pi in MPI C
 ============================================================================
 */
#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

void Llenar(int vec[],int n);
int Separar(int x[],int y[],int comm_sz,int my_rank,int n);

int main(int argc, char *argv[])
{
	int Etiqueta1=0,Etiqueta2=1;
	int Etiqueta3=2,Etiqueta4=3;
	MPI_Status status;
	//Mis variables
	int n;
	int suma_local=0,suma_global=0;


	//Variables mpi
	int comm_sz; /* Number of processes */
	int my_rank; /* My process rank */
	//Fin variables mpi

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	printf("Ingrese la dimension del vector:");
	scanf("%d",&n);
	int x[n],y[n];
	int z[1];

	if(my_rank==0)
	{

		printf("Ingrese las tareas:");
		scanf("%d",&comm_sz);

		Llenar(x,n);
		Llenar(y,n);

		for (int q = 1; q < comm_sz-1; q++) {

			MPI_Send(x, n, MPI_INT, Etiqueta1, q, MPI_COMM_WORLD);
			MPI_Send(y, n, MPI_INT, Etiqueta2, q, MPI_COMM_WORLD);

			//MPI_Recv(x, n, MPI_INT, Etiqueta3, q, MPI_COMM_WORLD, &status);
			//MPI_Recv(y, n, MPI_INT, Etiqueta4, q, MPI_COMM_WORLD, &status);
			MPI_Recv(z, 1, MPI_INT, Etiqueta3, q, MPI_COMM_WORLD, &status);
			suma_global=suma_global+z[0];
		}
		printf("La suma total es %d:",suma_global);

	}else{
		for (int q = 1; q < comm_sz-1; q++) {

			MPI_Recv(x, n, MPI_INT, Etiqueta1, q, MPI_COMM_WORLD, &status);
			MPI_Recv(y, n, MPI_INT, Etiqueta2, q, MPI_COMM_WORLD, &status);

			suma_local=Separar(x,y,comm_sz,my_rank,n);
			z[0]=suma_local;
			//MPI_Send(x, n, MPI_INT, Etiqueta3, q, MPI_COMM_WORLD);
			//MPI_Send(y, n, MPI_INT, Etiqueta4, q, MPI_COMM_WORLD);
			MPI_Send(z, 1, MPI_INT, Etiqueta3, q, MPI_COMM_WORLD);
		}

	}
}

void Llenar(int vec[],int n)
{
	srand(time(NULL));
	for(int i=0;i<n;i++)
	{
		int ran=(1+rand()%(100-1));
		vec[i]=ran;
	}
}

int Separar(int x[],int y[],int comm_sz,int my_rank,int n)
{
	int tope=my_rank*(n/(comm_sz-1));
	int suma=0;
	int i=tope-10;

	for(;i<tope;i++)
	{
		suma=suma+x[i]+y[i];
	}
	return suma;
}
