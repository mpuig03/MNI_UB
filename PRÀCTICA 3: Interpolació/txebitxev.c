/*Marc Puig Creixell*/
/*Funció que calcula un 0 del polinomi de Txebitxev de grau n  amb un valor inicial x0.
Amb maxim d'iteracions "iter" i tolerancia "tol" */
#include<math.h>
#include "txebitxev.c"

int newtraph(int n, double x0, int iter, double tol, double *arrel){
    int i;
    double f, df;
    for(i=0;i<iter;i++){
        txebitxev(n,x0,&f,&df);
        if(fabs(f)<=tol){
            return 0;
        }else if(fabs(df)<=tol){
            return -1;
        }
        *arrel=x0-f/df;
        if(fabs(*arrel-x0)<=tol){
            return 0;
        }
        x0=*arrel;
    }
    return -1;
}
