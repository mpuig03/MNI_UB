/*Marc Puig Creixell*/
/*Donada la forma de matriu de l'exercici 5.2, calcular el nombre de condició d'A(nxn) amb la norma sub-infinit de la matriu per diferents n*/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include "triU.c"
#include "triL.c"
#define DIM 30

void triU (double **U, double *b, int n);
void triL (double **U, double *b, int n);
int flud2 (double **a, int *p, int n, double tol); 
double norma_inf (double** A, int n);

int main(void){
	int i, j, n;
    int *p=NULL;
	double **A, **Ai, *ei;
    double A_inf, Ai_inf, tol=1e-8;

    
	printf("Introdueix n:\n");
    scanf(" %d",&n);

    /*RESERVA DE MEMORIA I COEFICIENTS*/
    A=(double**)malloc(n*sizeof(double*));
    Ai=(double**)malloc(n*sizeof(double*));
    if(A==NULL||Ai==NULL){
        printf("Error en la reserva de memoria.\n");
        return 1;
    }
    for(i=0;i<n;i++){
        A[i]=(double*)malloc(n*sizeof(double));
        Ai[i]=(double*)malloc(n*sizeof(double));
        if(A[i]==NULL||Ai[i]==NULL){
            printf("Error en la reserva de memoria.\n");
            return 1;
        }
    }

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            A[i][j]=pow(sqrt(i+2),j);
        }
    }

    A_inf=norma_inf(A,n); /*Calculem la norma abans de canviar A*/
    

    /*Cal pivotatge?*/
    printf("Cal utilitzar pivotatge?(1=sí,0=no)\n");
    scanf(" %d",&i);
    if(i==1){
        p=(int*)malloc(n*sizeof(int));
        for(i=0;i<n;i++) p[i]=i;
    }
    /*FACTORITZACIO*/
    if(flud2(A,p,n,tol)!=1){
        printf("No s'ha pogut fer la factorització LU\n");
        return 1;
    }
    
    /*CALCUL INVERSA*/
    /*vectors auxiliars identitat*/
    ei=(double*)malloc(n*sizeof(double));
    if(ei==NULL){
        printf("Error en la reserva de memoria\n");
        return 1;
    }

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(i==j){
                if(p==NULL){
                    ei[j]=1;
                }else{
                    ei[p[j]]=1;
                }
            }else{
                if(p==NULL){
                    ei[j]=0;
                }else{
                    ei[p[j]]=0;
                }
            }
        }
        /*Solucio n sistemes*/
        triL(A,ei,n);
        triU(A,ei,n);        
    
        for(j=0;j<n;j++){
            Ai[j][i]=ei[j];
        }
    }
    
    Ai_inf=norma_inf(Ai,n);
    printf("El nombre de condicio d'A és: k_inf= %22.15e\n", Ai_inf*A_inf);
    
    free(ei);
    if (p!= NULL){
        free(p);
    }
    for(i=0;i<n;i++){
        free(A[i]);
    }
    for(i=0;i<n;i++){
        free(Ai[i]);
    }
    free(A);
    free(Ai);
    return 0;
	
}

double norma_inf(double **A,int n){
    double max, sum;
    int i,j;
    max=0;

    for(i=0;i<n;i++){
        sum=0;
        for(j=0;j<n;j++){
            sum+=fabs(A[i][j]);
        }
        if(sum>max){
            max=sum;
        }
    }

    return max;
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