#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "struct.h"
#include "GetLen.h"
#include "GetDots.h"
#include "SortDots.h"
#include "SegmentUnion.h"

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

    //Получение количества концов отрезков
    int len = GetLen(input, output);
    rewind(input);
    
    struct point *dots = (struct point *) malloc(sizeof(struct point) * len);
    GetDots(len, dots, input);
    SortDots(len, dots);
    
    //Ввод отрезка
    struct point L;
    struct point R;
    double x0 = 0;
    double y0 = 0;
    int a = scanf("%lf", &x0);
    int b = scanf("%lf", &y0);
    
    if (a + b < 2){
        fprintf(output, "Ошибка ввода");
        fclose(input);
        fclose(output);
        return -1;
    }
    
    L.x = x0;
    R.x = y0;
    L.weight = 2;
    R.weight = 2;
    
    int res = SegmentUnion(len, dots, L, R);
    
    if (res == 1){
        fprintf(output, "Отрезок покрыт!\n");
    }
    else {
        fprintf(output, "Отрезок не покрыт!\n");
    }
    
    fclose(input);
    fclose(output);
    return 0;
}
