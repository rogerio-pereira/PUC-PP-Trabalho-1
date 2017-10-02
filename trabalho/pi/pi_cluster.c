#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <mpi.h>
#include "funcoes.h"

main(int argc, char *argv[])
{
    int ret,                    //Retorno do MPI
        rank,                   //No atual
        size,                   //Tamanho total do cluster
        i,                      //Iterador para os cluster slave
        tag = 0,                //Tag
        
    MPI_Status status;          //Status MPI

    //Variavies programa
    int vezes=0,
        iteradorVezes=0;
    double  numA=0.0,
            numB=0.0,
            totalIf=0.0,
            totalIfFinal=0.0,
            pi=0.0;
    unsigned long microSeconds=0.0;
    float milliSeconds=0.0;
    int seconds;
    clock_t start, end;
    bool first = true;

    //INICIA MPI
    ret = MPI_Init(&argc, &argv);
    ret = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    ret = MPI_Comm_size(MPI_COMM_WORLD, &size);

    //Nó 0
    if (rank == 0 && first == true)
    {
        vezes = numeroVezes();
        first = false;

        start = clock();

        for(i=0; i<size; i++) {
            //Envia o comando para o primeiro
            ret = MPI_Send(&vezes, 0, MPI_INT, i, tag, MPI_COMM_WORLD);
        }
    }

    if(first == true)
    {
        for(rankCounter=0; i<clusters; i++) {
            ret = MPI_Recv(&vezes, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);

            totalIf = calculaPi(vezes/size);

            //Envia o comando para o primeiro
            ret = MPI_Send(&totalIf, 0, MPI_INT, 0, tag, MPI_COMM_WORLD);
        }
    }
    else {
        ret = MPI_Recv(&totalIf, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);

        totalIfFinal += totalIf;

        end = clock();
        microSeconds = end - start;
        milliSeconds = microSeconds/1000;
        seconds = milliSeconds/1000;

        pi = totalIfFinal/vezes*4;

        printf("\nValor aproximado de PI %g\n\n", pi);
        printf("Tempo de execucao em microsegundos %lu\n", microSeconds);
        printf("Tempo de execucao em milisegundos %f\n", milliSeconds);
        printf("Tempo de execucao em segundos: %d\n", seconds);
    }

    ret = MPI_Finalize();
}
