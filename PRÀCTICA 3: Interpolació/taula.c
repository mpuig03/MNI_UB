#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "trap.c"

#define PI acos(-1.)

double g(double x);

int main(void){
    int j,n;
    FILE *f;

    f=fopen("taula.res","w");
    if(f==NULL){
        printf("Error d'obertura de fitxers.\n");
        return 1;
    }

    for(j=0;j<=20;j++){
        n=(int)ceil(sqrt((j*j*j*PI*PI*PI*exp(1)*100000)/12));
        fprintf(f,"%22.15e \t %22.15e\n",PI*j/10,trapezis(0.,PI*j/10,n,&g));
    }

    fclose(f);
    return 0;
}

double g(double x){
    return exp(sin(x));
}