#include <stdio.h>
#include <string.h>
#include "mpi.h"
main(int argc, char *argv[])
{
        int ret, rank, size, i, tag;
        MPI_Status status;
        char message[12];

        ret = MPI_Init(&argc, &argv);

        ret = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        ret = MPI_Comm_size(MPI_COMM_WORLD, &size);


	FILE *arquivo;
	char c, str[5]="Stark";
	int i;

        tag=100;
/*-----------------------------------------------------------------------------------------------------*/
        if (rank == 0)
        {
	if (!(arquivo = fopen("teste0.txt","r")))
  	{                           
  	  printf("Erro! Impossivel abrir o arquivo!\n");
  	  exit(1);
  	}
	
	while (!feof(arquivo))
 	{
        for(i=0;i<5;i++){

            c = getc(arquivo);
            if(c==str[i]){
                printf("letra encontrada %c", c);
                if(i==4){
                    printf("\npalavra encontrada\n");
			break;
                }
            }
            else{
                i=5;
            }
                        ret = MPI_Send(message, 12, MPI_CHAR, i, tag, MPI_COMM_WORLD);


/*----------------------------------------------------------------------------------------------------*/
        }
   	 if (rank == 1)
        {
	if (!(arquivo = fopen("teste1.txt","r")))
  	{                           
  	  printf("Erro! Impossivel abrir o arquivo!\n");
  	  exit(1);
  	}

	while (!feof(arquivo))
 	{
        for(i=0;i<5;i++){

            c = getc(arquivo);
            if(c==str[i]){
                printf("letra encontrada %c", c);
                if(i==4){
                    printf("\npalavra encontrada\n");
			break;
                }
            }
            else{
                i=5;
            }
               
                        ret = MPI_Send(message, 12, MPI_CHAR, i, tag, MPI_COMM_WORLD);
        }
/*---------------------------------------------------------------------------------------------------------*/
   	/* if (rank == 2)
        {
	if (!(arquivo = fopen("teste2.txt","r")))
  	{                           
  	  printf("Erro! Impossivel abrir o arquivo!\n");
  	  exit(1);
  	}

	while (!feof(arquivo))
 	{
        for(i=0;i<5;i++){

            c = getc(arquivo);
            if(c==str[i]){
                printf("letra encontrada %c", c);
                if(i==4){
                    printf("\npalavra encontrada\n");
			break;
                }
            }
            else{
                i=5;
            }
             
                        ret = MPI_Send(message, 12, MPI_CHAR, i, tag, MPI_COMM_WORLD);
        }
/*------------------------------------------------------------------------------------------------------------*/
 	   /*if (rank == 3)
        {
              
                        ret = MPI_Send(message, 12, MPI_CHAR, i, tag, MPI_COMM_WORLD);
        }*/
        /*else
                
                ret = MPI_Recv(message, 12, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);

        printf("Mensagem do no %d : %s\n", rank, message);*/
        ret = MPI_Finalize();
}
