#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "mpi.h"
#include "funcoes.h"

main(int argc, char *argv[])
{
    int ret,                    //Retorno do MPI
        rank,                   //No atual
        rankCounter,            //Contador do rank usado no for
        size,                   //Tamanho total do cluster
        i,                      //Iterador para os cluster slave
        tag = 0,                //Tag 0 - Continua calculando fatorial, 1 - Resultado
        clusters,               //Quantidade a ser usada dos clusters
        nextRank,               //Próximo nó
        parametros[4],          //Parametros[numero, menorValor, maiorValor, resultado]
        *parametrosProximo,   //Parametros[numero, menorValor, maiorValor, resultado]
        result = 1;

    bool first = true;       //Primeiro nó

    MPI_Status status;          //Status MPI

    //INICIA MPI
    ret = MPI_Init(&argc, &argv);
    ret = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    ret = MPI_Comm_size(MPI_COMM_WORLD, &size);

    //Nó 0
    if (rank == 0)
    {
        //Se for primeira vez que executa o programa
        if(first == true) {
            parametros[0] = setNumber();    //Define o numero do fatorial
            parametros[3] = 0;              //Resultado = 0;

            //Define se vai selecionar quantidade de clusters ou não
            if(setCluster() == true)
                clusters = setClusterCount();
            //Se não clusters vão ser a quantidade total dos clusters
            else
                clusters = size;

            parametros[1] = 0;                  //Valor menor
            parametros[2] = (parametros[0]/size) -1;   //Valor Maior

            //Define que não é mais o primeiro
            first = false;
        
            //Define os parametros para o proximo nó
            parametrosProximo = defineIntervalo(parametros, size, rank);

            //Envia o comando para o primeiro
            ret = MPI_Send(&parametrosProximo, 0, MPI_INT, 1, tag, MPI_COMM_WORLD);
        }
        //Não é primeira vez que executa
        else {
            //Recebe os valores do no anterior
            ret = MPI_Recv(&parametros, 0, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);

//CODIGO REDUNDATE (63 - 80) E (97 - 114)
            //Ainda tem outros nós
            if(tag == 0) {
                //Chegou no final dos clusters
                if(rank+1 < clusters) {
                    nextRank = 0;
                    tag = 1;
                }
                //Não é o final dos clusters
                else {
                    nextRank++;
                }
        
                //Define os parametros para o proximo nó
                parametrosProximo = defineIntervalo(parametros, size, rank);

                //Envia o comando para o proximo
                ret = MPI_Send(&parametrosProximo, 0, MPI_INT, nextRank, tag, MPI_COMM_WORLD);

                //Calcula Fatorial do intervalo
                parametros[3] = calculaFatorial(parametros[2], parametros[1]);

                //Contabiliza o resultado
                result *= parametros[3];
            }
            //Terminou, Contabiliza o resultado
            else {
                result *= parametros[3];
            }
        }
    }

    for(rankCounter=0; i<clusters; i++) {
        //Recebe os valores do no anterior
        ret = MPI_Recv(&parametros, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);

//CODIGO REDUNDATE (69 - 86) E (97 - 114)
        //Chegou no final dos clusters
        if(rank+1 < clusters) {
            nextRank = 0;
            tag = 1;
        }
        //Não é o final dos clusters
        else {
            nextRank++;
        }
        
        //Define os parametros para o proximo nó
        parametrosProximo = defineIntervalo(parametros, size, rank);

        //Envia o comando para o proximo
        ret = MPI_Send(&parametrosProximo, 0, MPI_INT, nextRank, tag, MPI_COMM_WORLD);

        //Calcula Fatorial do intervalo
        parametros[3] = calculaFatorial(parametros[2], parametros[1]);

        //Envia o resultado para o nó 0
        ret = MPI_Send(&parametros, 0, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }

    printf("Valor do fatorial de %d: %d", parametros[0], result);
    ret = MPI_Finalize();
}
