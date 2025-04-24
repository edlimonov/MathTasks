#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "struct.h"

//Обработка input: количество чисел четное и их больше нуля
int GetLen(FILE *input, FILE *output) {
    int len = 0; double n;
    while(fscanf(input, "%lf", &n) == 1) len++;

    if ((len == 0) || (len%2 != 0)){
        fprintf(output, "Недостаточно данных");
        fclose(input);
        fclose(output);
        return -1;
    }
    return (len);
}
