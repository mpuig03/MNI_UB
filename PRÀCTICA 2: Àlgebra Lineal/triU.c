/*Marc Puig Creixell*/
/*La funció triU resol un sistema triangular superior de dimensió n amb matriu U i terme independent b*/

#include<stdio.h>
#include<math.h>

void triU (double **U, double *b, int n){
	int i,j;
	double tol=1e-8;

	for (i=n-1;i>=0;i--){
		if(fabs(U[i][i])<tol){
			printf("Error al intentar dividir per 0\n");
			return;
		}

		for(j=i+1;j<n;j++){
			b[i]-=U[i][j]*b[j];
		}

		b[i]=b[i]/U[i][i];
	}
	
	return;
}
