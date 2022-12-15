/*Marc Puig Creixell*/
/*Calcula les solucions d'un sistema triangular inferior (desat a M) amb terme independent b i les desa a c*/

void triangular(double**M, int n, double*b, double*c){
	int i,j;

	for (i=0;i<n;i++){
        c[i]=b[i];
		for(j=i-1;j>=0;j--){
			c[i]-=M[i][j]*c[j];
		}
        c[i]=c[i]/M[i][i];
	}
	
	return;
}