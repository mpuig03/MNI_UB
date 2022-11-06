/*Marc Puig Creixell*/
/*La funció triL resol un sistema triangular inferior de dimensió n amb matriu L i terme independent b*/

void triL (double **U, double *b, int n){
	int i,j;

	for (i=1;i<n;i++){
		for(j=0;j<i;j++){
			b[i]-=U[i][j]*b[j];
		}
	}
	
	return;
}
