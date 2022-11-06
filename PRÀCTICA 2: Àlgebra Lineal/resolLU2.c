/*Marc Puig Creixell*/
/*Modificació del resolLU1.c per tal de, donada la matriu A_lambda, trobar per quins valors de lambda es pot factoritzar sense pivotatge*/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

int flud2 (double **a,int *p, int n, double tol);
int main(void){
    int n,i,j,k;
    int compt1=0, compt2=0, iter=1e5;
    double tol, eps;
    double lambda;
    int *p;
    double **a;
    srand(time(NULL));

    printf("Introdueix el valor de n:\n");
    scanf("%d",&n);
    printf("Introdueix la tolerancia i l'epsilon:\n");
    scanf(" %le %le",&tol, &eps);

    a=(double**)malloc(n*sizeof(double*));
    if(a==NULL){
        printf("Error de reserva de memoria.\n");
        return 1;
    }
    
    for(i=0;i<n;i++){
        a[i]=(double*)malloc(n*sizeof(double));
        if(a[i]==NULL){
            printf("Error de reserva de memoria.\n");
            return 1;
        }
    }


    for(k=0;k<iter;k++){
        p=NULL;
        lambda=(5-eps)+(rand()/(double)RAND_MAX)*2*eps;
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                if(i!=j){
                    a[i][j]=-1.;
                }else{
                    a[i][j]=lambda;
                }
            }
            
        }
        
        if(flud2(a,p,n,tol)==1){
            compt1+=1;
        }
        p=(int*)malloc(n*sizeof(int));
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                if(i!=j){
                    a[i][j]=-1.;
                }else{
                    a[i][j]=lambda;
                }
            }
            p[i]=i;
        }
        if(flud2(a,p,n,tol)==1){
            compt2+=1;
        }

    }

    printf("s'ha pogut fer factorització LU(sense pivotatge) amb %d / %d casos.\n",compt1,iter);
    printf("s'ha pogut fer factorització LU(usant pivotatge) amb %d / %d casos.\n",compt2,iter);

    for(i=0;i<n;i++){
        free(a[i]);
    }
    free(a);
    return 0;    
}

int flud2(double **a, int *p, int n, double tol){
    int i,j,k,maxInd, aux;
    double pivot, *fila_temp;

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
    return 1;
}