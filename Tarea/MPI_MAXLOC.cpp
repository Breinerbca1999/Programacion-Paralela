
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>

struct Proceso{
	double val;
	int rank;
}in[30],out[30];

int main(int argc, char* argv[])
    {
        MPI_Init(&argc, &argv);

        // Obtenga el número de procesos y verifique que solo se utilicen 4.
        int size;
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        if(size != 4)
        {
            printf("Esta aplicación está diseñada para ejecutarse con 4 procesos.\n");
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
        }

        // Determinar el rango de la raíz
        int root_rank = 0;

        // Get my rank
        double ain[30],aout[30];
        int ind[30];
        int i;
        int my_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

        // Cada proceso MPI envía su rango a reducción,
        // el proceso raíz MPI recoge el resultado
        for(i=0;i<30;i++)
        {
        	in[i].val=ain[i];
        	in[i].rank=my_rank;
        }

        MPI_Reduce(&in, &out, 30, MPI_DOUBLE_INT, MPI_MAXLOC, root_rank, MPI_COMM_WORLD);


        if(my_rank == root_rank)
        {
            for(i=0;i<30;i++)
            {
            	aout[i]=out[i].val;
            	ind[i]=out[i].rank;
            }
        }

        MPI_Finalize();

        return EXIT_SUCCESS;
    }
