/*Marc Puig Creixell*/

/* Calcula els 50 primers termes de la successió x_0=0.1, x_n+1= 3.9(xn(1-xn).
 * Variables de tipus float*/

#include<stdio.h>
#include<math.h>

int main(void){
	float xn;
	double en;
	int i;

	en=0.1*1.19e-7;
	xn=0.1;
	printf("x_ 0 =  %22.15e +/- %22.15e\n",xn,en);
	for (i=1;i<=50;i++){
		en=fabs((3.9-7.8*xn)*en);
		xn=3.9*xn*(1-xn);
		printf("x_%2d = %22.15e +/- %22.15e\n",i,xn,en);
	}

	return 0;
}
