void iniciaMPI()
{
    ret = MPI_Init(&argc, &argv);
    ret = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    ret = MPI_Comm_size(MPI_COMM_WORLD, &size);
}

unsigned long long int numeroVezes()
{
    unsigned long long int vezes=0;

    printf("Digite o numero de vezes para ralizar o calculo\n");
    fflush(stdout);
    fflush(stdin);
    scanf("%llu", &vezes);

    return vezes;
}

int calculaPi(int vezes)
{
    int totalIf, i;
    double  numA,
            numB;

    for(i=0; i<vezes; i++) {
        numA = (double)rand()/RAND_MAX; //valor Aleatorio de 0.0 a 1.0
        numB = (double)rand()/RAND_MAX; //valor aleatorio de 0.0 a 1.0

        numA = numA * numA;
        numB = numB * numB;

        if((numA + numB) <= 1)
            totalIf++;
    }

    return totalIf;
}