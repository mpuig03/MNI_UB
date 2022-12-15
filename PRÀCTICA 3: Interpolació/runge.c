/*Marc Puig Creixell*/
/*Fenomen de Runge. Calcul dels valors de f(x)=1/(1+x²) en una xarxa equiespaiada en [-5,5], 
calcul del seu polinomi interpolador, i comparació a diferents nivells de finesa de la xarxa.*/

/*Per fer la comparacio simplement cal executar el programa dos cops amb dos valors de passos diferents*/

/*També hi ha inclosa la versió amb abcisses de Txebitxev */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "interpola.c"
#include "avalua.c"
#define PI acos(-1.)

int main(void){
    int i, n;
    double xi, p, *xtxeb,*x, *f,*ftxeb, *c,*ctxeb;
    char nom1[30], nom2[30];
    FILE *fit,*fitxeb;

    printf("introdueix el nombre de passos de la xarxa\n");
    scanf(" %d", &n);
    printf("introdueix el nom del fitxer de sortida(amb abcisses equiespaiades)\n");
    scanf(" %s", nom1);
    printf("introdueix el nom del fitxer de sortida (amb abcisses de Txebitxev):\n");
    scanf(" %s",nom2);

    fit=fopen(nom1,"w");
    fitxeb=fopen(nom2,"w");
    if(fit==NULL||fitxeb==NULL){
        printf("Error en l'obertura de fitxers\n");
        return 1;
    }

    x=(double*)malloc(n*sizeof(double));
    xtxeb=(double*)malloc(n*sizeof(double));
    f=(double*)malloc(n*sizeof(double));
    ftxeb=(double*)malloc(n*sizeof(double));
    c=(double*)malloc(n*sizeof(double));
    ctxeb=(double*)malloc(n*sizeof(double));
    if(f==NULL || x==NULL||c==NULL){
        printf("Error en la reserva de memoria\n");
        return 1;
    }
    if(ftxeb==NULL || xtxeb==NULL||ctxeb==NULL){
        printf("Error en la reserva de memoria\n");
        return 1;
    }
    p=10./(n-1);

    for(i=0;i<=n;i++){
        x[i]=-5+p*i;
        f[i]=1./(1+x[i]*x[i]);

        xtxeb[i]=5*cos(((2*i+1)*PI)/(2*(n+1)));
        ftxeb[i]=1./(1+xtxeb[i]*xtxeb[i]);
    }

    interpola(x,f,n,c);
    interpola(xtxeb,ftxeb,n,ctxeb);

    p=10./(n*200-1);
    
    xi=-5;
    for(i=0;i<=200*n;i++){
        fprintf(fit," %22.15e \t %22.15e\n",xi, avalua(xi,x,c,n));
        fprintf(fitxeb," %22.15e \t %22.15e\n",xi, avalua(xi,xtxeb,ctxeb,n));
        xi+=p;
    }

    fclose(fit);
    fclose(fitxeb);
    free(x);
    free(xtxeb);
    free(c);
    free(ctxeb);
    free(f);
    free(ftxeb);

    return 0;
}