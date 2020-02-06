/*
 ============================================================================
 Name        : Practica_01.c
 Author      : Correa Atucsa Breiner
 Version     :
 Copyright   : Your copyright notice
 Description : Compute Pi in MPI C++
 ============================================================================
 */

#include <math.h>
#include "mpi.h"
#include <iostream>
#include <time.h>
using namespace std;

int main(int argc, char *argv[]) {
	int size,rank;
    //Variables Globales
	int n,Factorial;
    int A[n];
	int x;
	int contador=0;

    //Variable Local
	int Suma;

	MPI_Status estado;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if(rank==0)
	{
		cout<<"Digite su num de elementos:";
		cin>>n;
		A[n];
		cout<<"Digite su valor a buscar:";
		cin>>x;
	}
	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&x,1,MPI_INT,0,MPI_COMM_WORLD);


	//Llenando Vector
		if(rank==0)
		{
			 srand(time(NULL));
			 for(int i=0;i<n;i++)
			 {
			    int val=rand()%10;
			    cout<<"\n val es:"<<val<<"\n";
			    A[i]=val;
			 }
			 cout<<"\n";
		}
	//Fin llenando el vector

	int pos=(n/size)*rank;
	contador=0;
	for(int i=0;i<=n/size;i++)
	{
		if(x==A[pos])
		{
			contador++;
		}
		pos=pos+1;
	}
	MPI_Reduce(&contador,&Suma,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

	if(rank==0)
	{
		cout<<"Las veces que aparecio "<<x<<"fueron :"<<Suma<<"\n";
	}

	MPI_Finalize();
	return 0;
}
