#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "struct.h"

//Сортировка массива точек по координате без учета типа
void SortDots(int len, struct point *array){
    int tmp = 0;
    for (int i = 0; i < len - 1; i++){
        for (int j = 0; j < len - i - 1; j++){
            if (array[j].x > array[j+1].x){
                tmp = array[j].x;
                array[j].x = array[j+1].x;
                array[j+1].x = tmp;
            }
        }
    }
}
