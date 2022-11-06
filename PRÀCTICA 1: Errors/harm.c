/*Marc Puig Creixell*/

/*Fer un programa en C que calcula la sèrie harmònica terme a terme. 
El programa hauria de parar quan sn-1 (sn1) = sn. 
Després es repeteix la suma des del màxim valor de n aconseguit en ordre invers*/

#include<stdio.h>

int main(void){
    float sn, sn1=-1;
    int i;

    sn=0;
    for(i=1;sn!=sn1;i++){
        sn1=sn;
        sn+=1./i;
    }

    printf("n=%d\n",i);
    printf("sn= %e\n",sn);

    /*suma en ordre invers*/
    sn=0;
    sn1=1;
    for(i=i;sn!=sn1 && i>0;i--){
    	sn1=sn;
   	sn+=1./i;
    }
    
   printf("sn (en ordre invers)= %e\n",sn);
    return 0;
}
