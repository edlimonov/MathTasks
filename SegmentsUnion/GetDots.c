#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "struct.h"

//Записываю в один массив концы отрезков с указанием типа
void GetDots(int len, struct point *array, FILE *input){
    
    bool A = true;
    for (int i = 0; i < len; i++){
        if (A == true){
            fscanf(input, "%lf", &array[i].x);
            array[i].weight = 1;
            A = false;
        }
        else {
            fscanf(input, "%lf", &array[i].x);
            array[i].weight = -1;
            A = true;
        }
    }
}
