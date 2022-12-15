/*Marc Puig Creixell*/
/*Funció main que, utilitzant la funció "newtraph" troba totes les arrels del polinomi de 
Txebitxev ordenades ascendentment*/

#include<stdio.h>
#include<stdlib.h>
#include "newtraph.c"

int main(void){
    FILE *f;
    char nom[30];
    double x0,x1,tol, **res;
    int n, itermax, i, j,r;

    /*LECTURA DE n, tol i itermax*/
    printf("Introdueix el valor de n:\n");
    scanf(" %d",&n);
    if(n<0){
        printf("n no vàlida.\n");
        return 1;
    }
    printf("Introdueix la tolerància i el màxim d'iteracions:\n");
    scanf(" %le %d", &tol, &itermax);

    /*RESERVA DE MEMORIA*/
    res=(double**)malloc(n*sizeof(double*));
    if(res==NULL){
        printf("Error de reserva de memoria.\n");
    }
    for(i=0;i<n;i++){
        res[i]=(double*)malloc((i+1)*sizeof(double));
        if(res[i]==NULL){
            printf("Error de reserva de memoria.\n");
        }
    }

    /*BUSCAR ARRELS PER NEWTON-RAPHSON*/
    res[0][0]=0;
    for(i=1;i<n;i++){
        for(j=0;j<=i;j++){
            /*calcul x0*/
            if(j==0){
                x0=-1;
                x1=res[i-1][j];
            }else if(j==i){
                x0=res[i-1][j-1];
                x1=1;
            }else{
                x0=res[i-1][j-1]; 
                x1=res[i-1][j];
            }
            x0=(x0+x1)/2;
            
            /*crida a newtraph*/
            r=newtraph(i+1,x0, itermax,tol,*(res+i)+j);
            if(r==-1){
                printf("No s'ha pogut trobar una arrel.\n");
                return 1;
            }

        }
    }

    /*ESCRIPTURA A FITXER*/
    printf("Introdueix el nom del fitxer:\n");
    scanf( "%s", nom);
    f=fopen(nom,"w");
    if(f==NULL){
        printf("Error en l'obertura del fitxer.\n");
        return 1;
    }

    for(i=0;i<n;i++){
        fprintf(f,"Grau %d:\n\n",i+1);
        for(j=0;j<=i;j++){
            fprintf(f,"%22.15e\n",res[i][j]);
        }
        fprintf(f,"\n");
    }

    fclose(f);
    for(i=0;i<n;i++){
        free(res[i]);
    }
    free(res);

    return 0;
}