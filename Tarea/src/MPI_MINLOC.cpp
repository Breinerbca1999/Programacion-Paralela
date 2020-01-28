
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>


struct Proceso{
	double val;
	int index;
}in,out;

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

        int count,root_rank=0;
        int my_rank,min_rank,min_index;
        float min_val;
        int LEN=1000;
        float val[LEN];
        in.val=val[0];
        in.index=0;

        for(int i=1;i<count;i++)
        {
        	if(in.val>val[i])
        	{
        		in.val=val[i];
        		in.index=i;
        	}
        }

        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
        in.index=my_rank*LEN+in.index;


        MPI_Reduce(&in, &out, 1, MPI_FLOAT_INT, MPI_MAXLOC, root_rank, MPI_COMM_WORLD);


        if(my_rank == root_rank)
        {
            min_val=out.val;
            min_rank=out.index/LEN;
            min_index=out.index % LEN;
        }

        MPI_Finalize();

        return EXIT_SUCCESS;
    }
