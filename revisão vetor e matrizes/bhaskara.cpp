#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int main ()
{
	double A=0,B=0,C=0;
	
	scanf("%lf %lf %lf", &A, &B, &C);
	
	if ((A == 0) || ((sqrt( pow(B,2) - (4*(A*C )))) < 0 )) 
	{
		printf("Impossivel calcular\n");		
	}
	else 
	{
		double  d=0, x=0,x2=0;
		
		d= (pow(B,2) - (4*(A*C)));
		
		x = (B - d ) / (2*A);		
		
		x2 = ((0-B ) - d) / (2*A);	
	
		printf("R1 = %.5lf\n",x);
		printf("R2 = %.5lf",x2);
		
	}

return 0;
}
