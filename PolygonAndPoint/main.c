#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "cross.h"
#include "struct.h"
#include "GetLen.h"
#include "RecordDots.h"

int main(void) {

    //Проверка файлов
    FILE *input = fopen("/Users/nail/Desktop/proga_points /DOTS.txt", "r");
    if(input == NULL) return -1;
    
    FILE *output = fopen("/Users/nail/Desktop/proga_points /DOTSout.txt", "w");
    if(output == NULL){
        fclose(input);
        fclose(output);
        return -1;
    }
    
    //Получение количества точек
    int len = GetLen(input, output);
    rewind(input);
    
    //Создание массива точек
    struct point_2d *array = (struct point_2d *) malloc(sizeof(struct point_2d) * (len+1));
    RecordDots(input, array, (len+1));
    
    struct point_2d P;
    bool A = true;
    double x0 = 0;
    double y0 = 0;

    int first = scanf("%lf", &x0);
    int second = scanf("%lf", &y0);
    
    if (first + second < 2){
        fprintf(output, "Ошибка ввода");
        fclose(input);
        fclose(output);
        free(array);
        return -1;
    }
    
    P.x = x0;
    P.y = y0;
    
    int count = cross(array, len, P, input, output);
    
    if (count%2 == 1){
        fprintf(output, "Точка снаружи");
    } else {
        fprintf(output, "Точка внутри");
    }
    
    fclose(input);
    fclose(output);
    free(array);
    return 0;
}
