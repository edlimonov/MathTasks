#include <stdio.h>
#include <math.h>

double L (double x){
    return (7*x - 4);
}

double S (double x){
    return (x*x + 2*x - 1);
}

double T (double x){
    return (sin(x-M_PI/3));
}

double H (double x){
    return (pow(9, x-0.5) - 8*pow(3, x-2)-4);
}
