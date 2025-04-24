#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "struct.h"

int SegmentUnion(int len, struct point *array, struct point L, struct point R){

    int count = 0;
    //Проверка правой точки заданного отрезка
    for (int i = 0; i < len; i++){
        if (array[i].x < R.x){
            count += array[i].weight;
        } else break;
    }
    
    if (count == 0){
        return 2;
    }
    
    int count_main = 0;
    int flag_first = 0;
    
    //Проверка точек разбиения
    for (int i = 0; i < len; i++){
        
        if (array[i].x < R.x && array[i].x > L.x){

            //Для первой точки
            if (flag_first == 0){
                ++flag_first;

                for (int j = 0; j < len; i++){
                    if (array[j].x < array[i].x){
                        count += array[j].weight;
                    }
                }
                if (count_main == 0){
                    return 2;
                }
            }
            
            //Для остальных точек
            if (flag_first != 0){
                count_main += array[i-1].x;
                
                if (count == 0){
                    return 2;
                }
            }
        }
    }
    
    return 1;
}
