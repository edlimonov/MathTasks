#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*
 Формат входных данных:
 
 Первый аргумент командной строки - путь ко входному файлу
 Второй аргумент командной строки - путь к выходному файлу
 
 Во входном файле идут числа через пробел:
 
 Коэффициенты функции f(x) сначала a, потом b
 Целое число N - количество точек
 Точки через пробел
 
 Формат выходных данных:
 N чисел через пробел
 */

//функция с линейной и экспоненциальной частью вида f(x) = a * e^(x*b) + c * x + d
struct CombinedFunc {
    //коэффициенты экспоненциальной части
    double a;
    double b;
    
    //коэффициенты линейной части
    double c;
    double d;
};

double Exponent(double x, double a, double b) {
    return a * exp(x * b);
}

double Linear(double x, double a, double b) {
    return x * a + b;
}

//вычисляет значение комбинированной функции
double ComputeCombined(struct CombinedFunc func, double x) {
    
    double exp = Exponent(x, func.a, func.b);
    double linear = Linear(x, func.c, func.d);
    
    return exp + linear;
}

//вычисляет значение производной комбинированной функции в точке
double DeriveCombined(struct CombinedFunc func, double x) {
    return func.a * func.b * exp(func.b * x) + func.c;
}

struct CombinedFunc FirstTransform(struct CombinedFunc first, struct CombinedFunc second){
    struct CombinedFunc result;
    
    result.a = first.a - first.b;
    result.b = first.b;
    result.c = first.c - second.c;
    result.d = first.d - second.d;
    
    return result;
}

struct CombinedFunc SecondTransform(struct CombinedFunc first, double x){
    struct CombinedFunc result;
    
    result.a = first.a;
    result.b = first.b;
    result.c = first.c + DeriveCombined(first, x);
    result.d = first.d - DeriveCombined(first, x) * x;
    
    return result;
}

//закрывает файлы и выводит служебную информацию
void Close(FILE *input, FILE *output) {
    fprintf(output, "Недостаточно данных");
    fclose(input);
    fclose(output);
}

int main(int argc, const char * argv[]) {
    
    FILE *input = fopen(argv[1], "r");
    if(input == NULL) {
        return -1;
    }
    
    FILE *output = fopen(argv[2], "w");
    if(output == NULL){
        fclose(input);
        return -1;
    }
    
    double a, b;
    
    if (fscanf(input, "%lf", &a) != 1 || fscanf(input, "%lf", &b) != 1) {
        Close(input, output);
        return -1;
    }
    
    struct CombinedFunc first;
    
    first.a = a;
    first.b = b;
    first.c = 0;
    first.d = 0;
    
    int num;
    
    if (fscanf(input, "%d", &num) != 1) {
        Close(input, output);
        return -1;
    }
    
    double *dots_in = (double *) malloc(sizeof(double) * num);
    
    for (int i = 0; i < num; i++){
        if (fscanf(input, "%lf", &dots_in[i]) != 1){
            Close(input, output);
            return -1;
        }
    }
    
    double *dots_out = (double *) malloc(sizeof(double) * num);
    
    double x_0;
    struct CombinedFunc second;
    
    second.a = 0;
    second.b = 0;
    second.c = 0;
    second.d = 0;
    
    for (int i = num - 1; i >= 0; i--){
        
        x_0 = dots_in[i];
        
        //первое преобразование
        first = FirstTransform(first, second);
        
        //второе преобразование
        second = SecondTransform(first, x_0);
        
        dots_out[i] = ComputeCombined(second, 0);
    }
    
    for (int i = 0; i < num; i++){
        fprintf(output, "%lf ", dots_out[i]);
    }
    
    fclose(input);
    fclose(output);
    
    printf("Success!");
    
    return 0;
}
