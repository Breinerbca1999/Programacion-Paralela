    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <mpi.h>

    /**
     * @brief Illustrates how to use a logical exclusive or reduction operation.
     * @details This application consists of a logical exclusive or reduction; every
     * MPI process sends its value for reduction before the logical exclusive or of
     * these values is stored in the root MPI process. It can be visualised as
     * follows, with MPI process 0 as root:
     *
     * +-----------+ +-----------+ +-----------+ +-----------+
     * | Process 0 | | Process 1 | | Process 2 | | Process 3 |
     * +-+-------+-+ +-+-------+-+ +-+-------+-+ +-+-------+-+
     *   | Value |     | Value |     | Value |     | Value |
     *   | false |     | false |     | false |     | true  |
     *   +-------+     +-------+     +-------+     +-------+
     *            \         |           |         /
     *             \        |           |        /
     *              \       |           |       /
     *               \      |           |      /
     *                +-----+-----+-----+-----+
     *                            |
     *                        +---+---+
     *                        |  LXOR |
     *                        +---+---+
     *                            |
     *                        +---+---+
     *                        |  true |
     *                      +-+-------+-+
     *                      | Process 0 |
     *                      +-----------+
     **/
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
        int my_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

        // Cada proceso MPI envía su rango a reducción,
        // el proceso raíz MPI recoge el resultado

        bool my_value = (my_rank == 3);
        bool reduction_result = false;
        MPI_Reduce(&my_value, &reduction_result, 1, MPI_C_BOOL, MPI_LXOR, root_rank, MPI_COMM_WORLD);

        if(my_rank == root_rank)
        {
            printf("La lógica exclusiva o de todos los valores es %s.\n", reduction_result ? "true" : "false");
        }

        MPI_Finalize();

        return EXIT_SUCCESS;
    }
