/*Marc Puig Creixell*/
/*Avalua, mitjançant el mètode de Horner, un polinomi interpolador de forma c0+c1(x-x0)+...+c_n-1(x-x0)...(x-x_n-2) en el punt z*/

double avalua(double z, double *x, double *c, int n){
    int i;
    double val;

    val=c[n-1];
    for(i=n-2;i>=0;i--){
        val=val*(z-x[i])+c[i];
    }
    return val;
}
