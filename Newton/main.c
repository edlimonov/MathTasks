#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Newton.h"
#include "Func.h"

int main(void) {
    
    double alpha;
    
    if (scanf("%lf", &alpha)!=1){
        printf("Incorrect!\n");
        return -1;
    } else if(alpha<0){
        printf("Решений нет!\n");
        return -1;
    }else if (alpha == 0){
        printf("Корень: 0\n");
        return -1;
    }
    
    printf("Вы ввели параметр: %lf\n", alpha);
    printf("Корень: %lf\n\n", RootFinder(alpha));
    
    return 0;
}

