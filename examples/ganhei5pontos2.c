#include <stdio.h>
#include <string.h>
main()
{
        int  i;

        int a=1;
	int b=1;
	int c=1;
	int d=1;
	int res;

			for(i=0; i<10000000000; i++){
			a = a*a;
			}
                
			for(i=0; i<10000000000; i++){
			b = b*b;
			}	
	
			for(i=0; i<10000000000; i++){
			c = c*c;
			}
			for(i=0; i<10000000000; i++){
			d = d*d;
			}
			
	
		res = a+b+c+d;
		printf("\nValor da soma: %d\n", res);

}
