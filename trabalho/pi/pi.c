/*
	Esso código calcula o valor de pi baseado na seguinte regra
renato.pitarello@gmail.com

ti@soitic.com

fazer 400000
criar numero aleatório entre 1 e 9
dividir por 10
elevar ao quadrado

criar outro numero aleatorio entre 1 e 9
dividir por 10
elevar ao quadrado

se for menor do que 1
 incrementa variavel

dividir por 100.000 (1/4 do valor de vezes)
 */

#include <stdio.h>
#include <string.h>
#include <mpi.h>

main(int argc, char *argv[])
{
        int ret, rank, size, i, tag;
        MPI_Status status;
        char message[12];

        ret = MPI_Init(&argc, &argv);

        ret = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        ret = MPI_Comm_size(MPI_COMM_WORLD, &size);

        tag=100;
        if (rank == 0)
        {
                strcpy(message,"Ola, Mundo!");

                for (i=0; i<size; i++)
                        ret = MPI_Send(message, 12, MPI_CHAR, i, tag, MPI_COMM_WORLD);
        }
        else
                
                ret = MPI_Recv(message, 12, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);

        printf("Mensagem do no %d : %s\n", rank, message);
        ret = MPI_Finalize();
}


