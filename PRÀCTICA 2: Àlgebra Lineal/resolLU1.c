/*Marc Puig Creixell*/
/*Llegeix una matriu nxn de sestemes lineals i una matriu B=nxm
de termes independents i usant les funcions anteriors escrigui
la matriu solucio X (nxm), el determinant d'A i calculi 
||A||_inf i ||X||_inf*/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include "triU.c"
#include "triL.c"
#include "flud.c"
#define DIM 30

void triU (double **U, double *b, int n);
void triL (double **U, double *b, int n);
int flud (double **a, int *p, int n, double tol, double *det);
double norma_inf (double** A, int n);

int main(void){
    FILE *f1,*f2;
	char nom1[DIM], nom2[DIM];
	int i, j, k, n, m, l;
    int *p=NULL;
	double **A, **B, *bi;
    double Adet, A_inf, X_inf, tol=1e-8;
    
	printf("Introdueix el nom del fitxer de la matriu A:\n");
	scanf(" %s",nom1);
	printf("Introdueix el nom del fitxer de la matriu B:\n");
	scanf(" %s",nom2);	
	
	/*OBERTURA FITXERS*/
	f1=fopen(nom1,"r");
	if(f1==NULL){
		printf("Error en l'obertura del fitxer\n");
		return 1;
	}

	f2=fopen(nom2,"r");
	if(f2==NULL){
		printf("Error en l'obertura del fitxer\n");
	}
	
	/*LECTURA FITXERS*/
	fscanf(f1,"%d %d",&n, &k);

    if(n!=k){
        printf("Matriu B incorrecta (%d != %d).\n",n,k);
        return 1;
    }

    A=(double**)malloc(n*sizeof(double*));

	if(A==NULL){
		printf("Error en la reserva de memoria\n");       
		return 1;
	}

	for(i=0;i<n;i++){
		*(A+i)=(double*)malloc(k*sizeof(double));

		if(A[i]==NULL){
			printf("Error en la reserva de memoria\n");       
			return 1;
		}
	}	

	for(i=0;i<n;i++){
		for(j=0;j<k;j++){
			fscanf(f1," %le",&A[i][j]);
		}

	}

    /*  IMPRESSIO A
    printf("A:\n");
    for(i=0;i<n;i++){
        for(j=0;j<k;j++){
            printf("%le ",A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    */

    fscanf(f2," %d %d",&l, &m);
    if(l!=n){
        printf("Matriu B incorrecta (%d != %d).\n",l,n);
        return 1;
    }

	B=(double**)malloc(n*sizeof(double*));

	if(B==NULL){
		printf("Error en la reserva de memoria\n");       
		return 1;
	}
    

	for(i=0;i<n;i++){
		*(B+i)=(double*)malloc(m*sizeof(double));

		if(B[i]==NULL){
			printf("Error en la reserva de memoria\n");       
			return 1;
		}
	}	

	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			fscanf(f2," %le",&B[i][j]);
		}

	}
    /* IMPRESSIO B
    printf("B:\n");
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            printf("%le ",B[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    */

    A_inf=norma_inf(A,n);
    
    /*Cal pivotatge?*/
    printf("Cal utilitzar pivotatge?(1=sí,0=no)\n");
    scanf(" %d",&i);
    if(i==1){
        p=(int*)malloc(n*sizeof(int));
        for(i=0;i<n;i++) p[i]=i;
    }
    if(flud(A,p,n,tol,&Adet)!=1){
        printf("No s'ha pogut fer la factorització LU\n");
        return 1;
    }

    /* IMPRESSIO VECTOR PERMUTACIONS
    if(p!=NULL){
        printf("Vector permutacions:\n");
        for(i=0;i<n;i++){
            printf("%d ",i);
        }
        printf("\n");
        for(i=0;i<n;i++){
            printf("%d ",p[i]);
        }
        printf("\n");
    }
    */

    /*Ara tenim L*U*X[i]=B[i] per i=0,...,m-1, 
    amb L i U guardades a la matriu A.
    Cal resoldre dos sistemes:
    Ly=b i Ux=y*/

    bi=(double*)malloc(n*sizeof(double));
    if(bi==NULL){
        printf("Error en la reserva de memoria\n");
        return 1;
    }

    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            if(p==NULL){
                bi[j]=B[j][i];
            }else{
                bi[j]=B[p[j]][i];
            }
        }
        triL(A,bi,n);
        triU(A,bi,n);

        for(j=0;j<n;j++){
            B[j][i]=bi[j];
        }   
        /*A bi quedara X[i], i bi passa a ser B[][i]*/
    }

    X_inf=norma_inf(B,n);
    printf("La matriu solució X=\n");
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            printf("%22.15e ",B[i][j]);
        }
        printf("\n");
    }
    
    printf("\n\ndet(A)= %22.15e\n",Adet);
    printf("||A||_inf= %22.15e\n",A_inf);
    printf("||X||_inf= %22.15e\n",X_inf);
    
    fclose(f1);
    fclose(f2);
    free(bi);
    if (p!= NULL){
        free(p);
    }
    for(i=0;i<n;i++){
        free(A[i]);
    }
    for(i=0;i<n;i++){
        free(B[i]);
    }
    free(A);
    free(B);
    return 0;
	
}

double norma_inf(double **A,int n){
    double max, sum;
    int i,j;
    max=A[0][0];

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
