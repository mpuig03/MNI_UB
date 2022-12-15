/*Funció que avalua el polinomi de Txebitxev de grau n i la seva derivada en el punt x*/

void txebitxev(int n, double x,double *f, double *df){
   double f1=x, f2=1, df1=1, df2=0;
   int i;

   if(n==1){
    *f=f1;
    *df=df1;
   }else if(n==0){
    *f=f2;
    *df=df2;
   }

    for(i=2;i<=n;i++){
        *f=2*x*f1-f2;
        *df=2*f1+2*x*df1-df2;

        f2=f1;
        f1=*f;

        df2=df1;
        df1=*df;
    }
}
