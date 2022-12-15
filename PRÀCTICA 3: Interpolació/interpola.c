/*Marc Puig Creixell*/
/*Crea la matriu amb els coeficients del sistema per trobar els c_i del polinomi i crida la funcio triangular per resoldre el sistema i trobar-los */

#include<stdio.h>
#include<stdlib.h>
#include "triangular.c"

void interpola(double *x, double *f, int n, double *c){
    double **M;
    int i,j;

    M=(double**)malloc(n*sizeof(double*));
    if(M==NULL){
        printf("Error de reserva de memoria\n");
        return;
    }
    for(i=0;i<n;i++){
        M[i]=(double*)malloc((i+1)*sizeof(double));
        if(M[i]==NULL){
            printf("Error de reserva de memoria\n");
            return;
        }
    }

    for(i=0;i<n;i++){
        M[i][0]=1.;
        for(j=1;j<=i;j++){
            M[i][j]=M[i][j-1]*(x[i]-x[j-1]);
        }
    }

    triangular(M,n,f,c);


    for(i=0;i<n;i++){
        free(M[i]);
    }
    free(M);
    return;
}
