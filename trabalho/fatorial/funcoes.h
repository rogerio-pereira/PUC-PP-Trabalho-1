/*
 * FUNCOES
 */
/**
 * Define o numero a ser calculado o fatorial
 * @return (int) número
 */
int setNumber()
{
    int number;
            
    printf("Digite um numero para ser calculado o fatorial:\n");
    fflush(stdout);
    fflush(stdin);
    scanf("%d", &number);

    return number;
}

/**
 * Define se o usuário vai definir o número total de cluster
 * @return (char) s/n
 */
bool setCluster()
{
    char setedCluster[1];

    printf("Deseja digitar o numero de clusters, (s/n)\n");
    fflush(stdout);
    fflush(stdin);
    scanf("%s", &setedCluster);

    if(strcmp(setedCluster, "s") == 0)
        return true;
    else if(strcmp(setedCluster, "n") == 0)
        return false;
    else
        setCluster();
}

/**
 * Define a quantidade de cluster para rodar o algoritmo
 * @return (int) quantidade de clusters
 */
int setClusterCount()
{
    int number;
            
    printf("Digite um numero de clusters:\n");
    fflush(stdout);
    fflush(stdin);
    scanf("%d", &number);

    return number;
}

/**
 * Define o intervalo para o proximo Nó
 * @param  (int[4])     //Parametros[numero, menorValor, maiorValor, resultado] 
 * @param  (int)        //Tamanho do Cluster
 * @param  (int)        //Nó Atual
 * @return (int[4])     //Parametros[numero, menorValor, maiorValor, resultado]   
 */
int * defineIntervalo(int parametros[], int size, int rank)
{
    //Menor Valor, recebe o maior valor do anterior + 1
    parametros[1] = parametros[2] + 1;

    /*
        Maior valor = valor/tamanho do cluster * o numero do nó -1
            O valor +2 se refere ao proximo nó, se fosse +1 pegaria o nó atual
            E se não tivesse somando nada pegaria o nó anterior
     */
    parametros[2] = ((parametros[0]/size) * rank + 2) -1;

    return parametros;
}

/**
 * Calcula o fatorial do maior até o menor
 * @param  (int) Valor maior do intervalo
 * @param  (int) Valor menor do intervalo
 * @return (int) Valor do fatorial do intervalo
 */
int calculaFatorial(int menor, int maior)
{
    int i;	
    int result = 1;

    for(i=maior; i>=menor; i--) {
        result *= result;
    }

    return result;
}
