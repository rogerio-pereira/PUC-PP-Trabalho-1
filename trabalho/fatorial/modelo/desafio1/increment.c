#include <stdio.h>
#include <string.h>
#include "mpi.h"
main(int argc, char *argv[])
{
    	int ret, rank, size, i, tag;
    	MPI_Status status;
    	int value = 0;

    	ret = MPI_Init(&argc, &argv);

    	ret = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    	ret = MPI_Comm_size(MPI_COMM_WORLD, &size);

    	tag=100;
    	if (rank == 0)
    	{
		      ret = MPI_Send(&value, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
    	}
	    else {
        	ret = MPI_Recv(&value, 1, MPI_INT, rank-1, tag, MPI_COMM_WORLD, &status);
     		value++;

		      if(rank+1 < size)
			     ret = MPI_Send(&value, 1, MPI_INT, rank+1, tag, MPI_COMM_WORLD);
    	}

	printf("Valor do no %d: %d\n", rank, value);

	ret = MPI_Finalize();
}
