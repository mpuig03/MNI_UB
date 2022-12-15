double trapezis(double a, double b,int n, double (*af)(double)){
    double x0,x1,itg=0;
    int j;

    for(j=0;j<n;j++){
        x0=a+j*(b-a)/n;
        x1=a+(j+1)*(b-a)/n;

        itg+=(x1-x0)*((*af)(x0)+(*af)(x1))/2;
    }
    return itg;
}