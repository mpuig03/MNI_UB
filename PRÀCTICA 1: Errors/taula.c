/*Marc Puig Creixell*/
/*Programa que fa una taula de valors de la funció demanada utilitzant sèries de Taylor per aproximar la funció.*/

#include<stdio.h>
#include<stdlib.h>

int main(void){
	FILE* f1;
	f1=fopen("func.dad","w");
	double x,y,d=1e-5;

	for(x=-1e-3;x<0;x+=d){
		y=-1./3 + x*x/30 - x*x*x*x/840;
		fprintf(f1,"%22.15e %22.15e\n",x,y);
	}

	for(x=1e-5;x<=1e-3;x+=d){
		y=-1./3 + x*x/30 -x*x*x*x/840;
		fprintf(f1,"%22.15e %22.15e\n",x,y);
	}

	fclose(f1);

	return 0;
}

