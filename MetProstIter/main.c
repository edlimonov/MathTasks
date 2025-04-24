#include <stdio.h>
#include <math.h>
#include "Func.h"
#include "Research.h"

 /*
 Метод простых итераций поиска корня

 Реализация исходя из условий на f(x):
 1. На [a,b] функция гарантированно имеет корень
 2. Корень единственен
 3. Функция непрерывна на [a,b]
 */

int main(void) {

    //Отрезок
    double a = 0;
    double b = 2;

    double roots[4] = {4./7, -1+sqrt(2), M_PI/3, log(5)/log(3)};
    
    for (int i = 3; i < 4; ++i){
        
        for (int j = 1; j < 20; ++j){
            int iter = (int)pow(2,j);
            printf("%d %lf\n", iter, fabs(roots[i] - ResearchFunc(a, b, iter, (Case)i)));
        }
        printf("\n");
    }
    
    return 0;
}
