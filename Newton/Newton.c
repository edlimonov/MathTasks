#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Func.h"
#include <float.h>
#include <stdbool.h>
#define EPS 1e-6

double Sign(double a){
    if (a>0) return 1;
    return -1;
}

double BestPrecision (double a, double b, double alpha){
    
    double prec = 0;
    while (b - a > EPS){
        
        double len = (b-a)/2;
        
        if (Sign(Fun(a, alpha))*Sign(Fun(a+len, alpha))<0){
            b = a + len;
        } else {
            a = a + len;
        }
        
    }
    prec = b;
    return prec;
}

double RootFinder(double alpha){
    
    double a = 0;
    double b = 1;
    
    //Ищу смену знака
    while (Sign(Fun(a, alpha))*Sign(Fun(b, alpha))>0){
        a = b;
        b *= 2;
    }
    
    printf("Приближение корня: [%lf, %lf]\n\n", a, b);
    
    //Нахождение корня
    double root = BestPrecision(a, b, alpha);
    
    return root;
}
