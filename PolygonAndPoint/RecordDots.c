#include <stdio.h>
#include "struct.h"

//Запись точек
void RecordDots(FILE *f, struct point_2d *array, int len){
    
    for (int i = 0; i < (len-1); i++) {
        double x, y;
        fscanf(f, "%lf", &x);
        fscanf(f, "%lf", &y);
        struct point_2d p;
        p.x = x;
        p.y = y;
        array[i] = p;
    }
    array[len] = array[0];
}
