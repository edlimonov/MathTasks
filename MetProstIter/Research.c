#include <stdio.h>
#include <math.h>
#include "Func.h"
#include "Research.h"

double L (double x);
double S (double x);
double T (double x);
double H (double x);

double ResearchFunc (double a, double b, double number, Case type){
    
    double x;
    double derivative;
    double del;
    
    
    switch (type) {
            
        case LINEAR:
            
            //Производная (псевдо)
            derivative = (L(b) - L(a))/(b-a);
            x = b;
            
            //Константа 1/f'(x)
            del = 1/derivative;

            for (int i = 0; i < number; i++){
                x = x - del*L(x);
            }
            
            break;
            
        case SQUARE:
            
            //Производная (псевдо)
            derivative = (S(b) - S(a))/(b-a);
            x = b;
            
            //Константа 1/f'(x)
            del = 1/derivative;

            for (int i = 0; i < number; i++){
                x = x - del*S(x);
            }
            
            break;
            
        case TRIGONOMETRIC:
            
            //Производная (псевдо)
            derivative = (T(b) - T(a))/(b-a);
            x = b;
            
            //Константа 1/f'(x)
            del = 1/derivative;

            for (int i = 0; i < number; i++){
                x = x - del*T(x);
            }
            
            break;
            
        case HITR:
            
            //Производная (псевдо)
            derivative = (H(b) - H(a))/(b-a);
            x = b;
            
            //Константа 1/f'(x)
            del = 1/derivative;

            for (int i = 0; i < number; i++){
                x = x - del*H(x);
            }
            
            break;
    }
    
    return x;
}
