    #include <stdio.h>
    #include <stdlib.h>
    #include <mpi.h>

    /**
     * @brief Illustrates how to use a bit-wise exclusive or reduction operation.
     * @details This application consists of a bit-wise exclusive or reduction;
     * every MPI process sends its value for reduction before the bit-wise exclusive
     * or of these values is stored in the root MPI process. It can be visualised as
     * follows, with MPI process 0 as root:
     *
     * +-----------+ +-----------+ +-----------+ +-----------+
     * | Process 0 | | Process 1 | | Process 2 | | Process 3 |
     * +-+-------+-+ +-+-------+-+ +-+-------+-+ +-+-------+-+
     *   | Value |     | Value |     | Value |     | Value |
     *   |   0   |     |   1   |     |   3   |     |   8   |
     *   +-------+     +-------+     +-------+     +-------+
     *            \         |           |         /
     *             \        |           |        /
     *              \       |           |       /
     *               \      |           |      /
     *                +-----+-----+-----+-----+
     *                            |
     *                        +---+---+
     *                        |  BXOR |
     *                        +---+---+
     *                            |
     *                        +---+---+
     *                        |   10  |
     *                      +-+-------+-+
     *                      | Process 0 |
     *                      +-----------+
     **/
    int main(int argc, char* argv[])
    {
        MPI_Init(&argc, &argv);

        // Obtenga el número de procesos y verifique que solo se utilicen 4.
        int size=4;
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        if(size != 4)
        {
            printf("Esta aplicación está diseñada para ejecutarse con 4 procesos.\n");
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
        }

        // Determine root's rank
        int root_rank = 0;

        // Get my rank
        int my_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

        // Cada proceso MPI envía su rango a reducción,
        // el proceso raíz MPI recoge el resultado
        char all_values[4] = {0, 1, 3, 8};
        char my_value = all_values[my_rank];
        char reduction_result = 0;
        MPI_Reduce(&my_value, &reduction_result, 1, MPI_UNSIGNED_CHAR, MPI_BXOR, root_rank, MPI_COMM_WORLD);

        if(my_rank == root_rank)
        {
            printf("La bit-wise exclusiva o de todos los valores es %d.\n", reduction_result);
        }

        MPI_Finalize();

        return EXIT_SUCCESS;
    }
