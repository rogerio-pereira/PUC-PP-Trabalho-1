#include <stdio.h>
#include <stdlib.h>

void main()
{
	int i=0;
	unsigned long long int;
	double 	numA=0.0,
		numB=0.0,
		totalIf=0.0,
		pi=0.0;
	unsigned long microSeconds=0.0;
	float milliSeconds=0.0;
	int seconds;
	clock_t start, end;

	printf("Digite o numero de vezes para ralizar o calculo\n");
	fflush(stdout);
	fflush(stdin);
	scanf("%llu", &vezes);

	start = clock();

	for(i=0; i<vezes; i++) {
		numA = (double)rand()/RAND_MAX; //valor Aleatorio de 0.0 a 1.0
		numB = (double)rand()/RAND_MAX; //valor aleatorio de 0.0 a 1.0

		numA = numA * numA;
		numB = numB * numB;

		if((numA + numB) <= 1)
			totalIf++;
	}

	end = clock();
	microSeconds = end - start;
	milliSeconds = microSeconds/1000;
	seconds = milliSeconds/1000;

	pi = totalIf/vezes*4;

	printf("\nValor aproximado de PI %g\n\n", pi);
	printf("Tempo de execucao em microsegundos %lu\n", microSeconds);
	printf("Tempo de execucao em milisegundos %f\n", milliSeconds);
	printf("Tempo de execucao em segundos: %d\n", seconds);
}
