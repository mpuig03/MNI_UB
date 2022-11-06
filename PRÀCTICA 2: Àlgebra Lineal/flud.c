/*Marc Puig Creixell*/
/*Calcula la factoritzacio PA=LU o A=LU i detA d'una matriu nxn,
usant eliminació gaussiana amb pivotatge maximal per columnes o sense pivotatge*/

#include<stdio.h>
#include<math.h>

int flud(double **a, int *p, int n, double tol, double *det){
    int i,j,k,maxInd, aux;
    double pivot, *fila_temp;
    *det=1.;
    if(p==NULL){
        /*ELIMINACIÓ GAUSSIANA*/
        for(i=0;i<n;i++){ 
            if(fabs(a[i][i])<tol){
                return 0;
            }
            for(j=i+1;j<n;j++){ 
                a[j][i]=a[j][i]/a[i][i];
                for(k=i+1;k<n;k++){
                    a[j][k]-=a[j][i]*a[i][k];
                }
            }
        }
        for(i=0;i<n;i++){
            *det *= a[i][i];
        }

        return 1;
    }

    /*PIVOTATGE MAXIMAL PER FILES*/
    for(i=0;i<n;i++){ 
        /*permutacio*/
        maxInd=i;
        for(j=i;j<n;j++){
            if(fabs(a[j][i])>fabs(pivot)){
                pivot=a[j][i];
                maxInd=j;
            }
        }
        if(maxInd!=i){
            fila_temp=a[i];
            a[i]=a[maxInd];
            a[maxInd]=fila_temp;

            aux=p[i];
            p[i]=p[maxInd];
            p[maxInd]=aux;

            *det*=-1;

        }

        for(j=i+1;j<n;j++){ 
            if(fabs(a[i][i])<tol){
                return 0;
            }
            a[j][i]/=a[i][i];
            for(k=i+1;k<n;k++){
                a[j][k]-=a[j][i]*a[i][k];
            }
        }
    }
    
    for(i=0;i<n;i++){
        *det *= a[i][i];
    }

    return 1;

}