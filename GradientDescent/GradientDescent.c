#include <stdio.h>
#include <math.h>
#include "Func.h"

double df (double x, double (*f)(double)){
    
    if (f == SquareFunc){
        return Sdf(x);
    }
    return Tdf(x);
    
}

double GradientDescent (double a, double learn_rate, double (*f)(double), int n){
    
    double x = a;
    
    for (int i = 0; i < n; i++){
        
        double grad = df(x, f);
        x -= learn_rate * grad;
        
    }
    
    return x;
}
