/*
 ============================================================================
 Name        : Practica_01.c
 Author      : Correa Atucsa Breiner
 Version     :
 Copyright   : Your copyright notice
 Description : Compute Pi in MPI C++
 ============================================================================
 */
#include "mpi.h"
#include <vector>
#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;

int main(int argc, char *argv[]) {
    int rank,size;
	int n;
    long long int local_prod, prod;
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        cout << "Ingrese el numero: ";
        cin>>n;
    }

    MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);

    local_prod = 1;
    for (int i = 0; i < n / size; i++) {
    	local_prod *= size*i+rank+1;
    }


    MPI_Reduce(&local_prod,&prod,1, MPI_LONG_LONG_INT, MPI_PROD, 0,MPI_COMM_WORLD);

    if (rank == 0)
        cout <<"El factorial de "<<n<< "! es  " << prod << endl;

    MPI_Finalize();
    return 0;
}
