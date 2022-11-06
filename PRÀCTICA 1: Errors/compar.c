/*Marc Puig Creixell*/

/*Comparació del càlcul de la successió utilitzant f(x)=3.9x(1-x) i g(x)=3.9x-3.9x²*/

#include<stdio.h>

int main(void){
	double xn, yn;
	int i;

	xn=0.1;
	yn=0.1;

	printf("x_ 0(f)= %22.15e  || x_ 0(g)= %22.15e\n",xn,yn);
	
	for(i=1;i<=50;i++){
		xn=3.9*xn*(1-xn);
		yn=3.9*yn-3.9*yn*yn;

		printf("x_%2d(f)= %22.15e  || x_%2d(g)= %22.15e\n",i,xn,i,yn);
	}

	return 0;

}
