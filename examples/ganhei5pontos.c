#include <stdio.h>
#include <string.h>
#include "mpi.h"
main(int argc, char *argv[])
{
        int ret, rank, size, i, tag;
        MPI_Status status;
       long  int a=1;
	long int b=1;
	long int c=1;
	long int d=1;
	long int res;

        ret = MPI_Init(&argc, &argv);

        ret = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        ret = MPI_Comm_size(MPI_COMM_WORLD, &size);

        tag=100;
        if (rank == 0)
        {
		for(i=0; i<10000000000; i++){
			a = a*a;
		}
                
                	ret = MPI_Recv(&b, 1, MPI_INT, 1, tag, MPI_COMM_WORLD, &status);
			ret = MPI_Recv(&c, 1, MPI_INT, 2, tag, MPI_COMM_WORLD, &status);
			ret = MPI_Recv(&d, 1, MPI_INT, 3, tag, MPI_COMM_WORLD, &status);
			res = a+b+c+d;
			printf("\n soma: %d", res);
	}

	else if (rank == 1)
        {	
			for(i=0; i<10000000000; i++){
			b = b*b;
			}	
			
                        ret = MPI_Send(&b, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
	}

	else if (rank == 2)
        {	
			for(i=0; i<10000000000; i++){
			c = c*c;
		}
			
                        ret = MPI_Send(&c, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
	}
	else if (rank == 3)
        {		
			for(i=0; i<10000000000; i++){
			d = d*d;
			}
			
                        ret = MPI_Send(&d, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
	}
	
		

        ret = MPI_Finalize();
}
