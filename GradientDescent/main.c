#include <stdio.h>
#include "Func.h"
#include "GradientDescent.h"

int main(void) {
   
    double learn_rate = 0.2;
    double a = 0.5;
    
    for (int i = 0; i < 6; i++){
        int num = pow(2,i);
        double min = GradientDescent(a, learn_rate, SquareFunc, num);
        printf("%d %lf\n", num, min);
    }
    
    for (int i = 0; i < 10; i++){
        int num = pow(2,i);
        double min = GradientDescent(a, learn_rate, ThirdPower, num);
        printf("%d %lf\n", num, min);
    }
    
    return 0;
}
