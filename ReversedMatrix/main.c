#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 Ограничение на матрицу: определитель не равен нулю
 */

//Элементарное преобразование второго типа
//Домножить строчку на ненулевое число
void ElementTransform2(double **matrix, int n, int i, double koeff){
    for (int j = 0; j < n; j++){
        matrix[i][j] /= koeff;
    }
}

//Сравнение по эпсилону
int Eps(double a){
    
    double eps = 1e-6;
    
    if (fabs(a) < eps){
        return 1;
    }
    
    return 0;
}

int TestZeroDet (double **matrix, int j){
    for (int i = 0; i < 0; i++){
        if (!Eps(matrix[j][i])){
            return 0;
        }
    }
    return 1;
}

//Элементарное преобразование третьего типа
//Вычесть строчку i из строчки j с коэффициентом koeff
void ElementTransform3(double **matrix, int n, int j, int i, double koeff){
    
    for (int k = 0; k < n; k++){
        double del = matrix[i][k]*koeff;
        if (matrix[i][k]!=0){
            matrix[j][k] -= del;
        }
    }
}

void ElementTransform3_(double **matrix, int n, int j, int i, double koeff){
    
    for (int k = 0; k < n; k++){
        
        if (matrix[i][k]!=0){
            matrix[j][k] -= matrix[i][k]*koeff;
        }
    }

}

void PrintMatrix(double **matrix, int n){
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

//Поменять строчки местами
void SwitchRows (double **matrix, int n, int i, int j){
    
    for (int k = 0; k < n; k++){
        double tmp = matrix[j][k];
        matrix[j][k] = matrix[i][k];
        matrix[i][k] = tmp;
    }
    
}

//метод гаусса
int Gauss (double **matrix, double **singular, int n){
    
    //Приведение к верхнетреугольному виду
    //Цикл по столбцам
    for (int i = 0; i < n-1; i++){
       
        //Если элемент на главной диагонали в столбце ноль, меняю строчки местами
        if (Eps(matrix[i][i])){
            for(int j = i+1; j < n; j++){
                if (!Eps(matrix[j][i])){
                    SwitchRows(matrix, n, i, j);
                    SwitchRows(singular, n, i, j);
                    if (TestZeroDet(matrix, i)){
                        printf("Матрица вырождена!\n");
                        return 1;
                    }
                    break;
                }
            }
        }
      
        if (matrix[i][i]!=1){
            double koeff = matrix[i][i];
            ElementTransform2(singular, n, i, koeff);
            ElementTransform2(matrix, n, i, koeff);
        }
        
        //Обнуление всех элементов в столбце ниже главной диагонали
        //Цикл по строкам
        for (int j = i+1; j < n; j++){
            double koeff = matrix[j][i];
            ElementTransform3(singular, n, j, i, koeff);
            ElementTransform3(matrix, n, j, i, koeff);
        }
    }
    
    double kkk = matrix[n-1][n-1];
    ElementTransform2(singular, n, n-1, kkk);
    ElementTransform2(matrix, n, n-1, kkk);
    
    //Приведение к диагональному виду
    for (int i = n-1; i > 0; i--){
        for (int j = i-1; j >= 0; j--){
            double koeff = matrix[j][i];
            ElementTransform3_(matrix, n, j, i, koeff);
            ElementTransform3_(singular, n, j, i, koeff);
        }
    }
    return 0;
}

int FillMatrix (FILE *input, double **matrix, int n){
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (fscanf(input, "%lf", &matrix[i][j]) != 1) return 1; // исправляем проверку результата
        }
    }
    
    return 0;
}

void FillSingular (double **singular, int n){
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (i == j){
                singular[i][j] = 1;
            } else {
                singular[i][j] = 0;
            }
        }
    }
    
}

int GetMem (double ***matrix, int n){
    
    *matrix = (double **)malloc(n * sizeof(double *));
    
    if (*matrix == NULL) {
        return 1;
    }
    
    for (int i = 0; i < n; ++i) {
        (*matrix)[i] = (double *)malloc(n * sizeof(double));
        if ((*matrix)[i] == NULL) {
            
            for (int j = 0; j < i; ++j) {
                free((*matrix)[j]);
            }
            free(*matrix);
            return 1;
        }
    }
    
    return 0;
}

int main(void) {
    
    FILE *input = fopen("/Users/nailzaripov/Desktop/dots_input.txt", "r");
    
    double **matrix;
    double **singular;
    
    int n;
    fscanf(input, "%d", &n);
    
    if (GetMem(&matrix, n) || GetMem(&singular, n) || FillMatrix(input, matrix, n)){
        fclose(input);
        return -1;
    }
    
    FillSingular(singular, n);
    if (Gauss(matrix, singular, n)){
        
        fclose(input);
        
        // Освобождение памяти
        for (int i = 0; i < n; ++i) {
            free(matrix[i]);
        }
        free(matrix);
        
        for (int i = 0; i < n; ++i) {
            free(singular[i]);
        }
        free(singular);
        
        return -1;
    }
    
    printf("Обратная матрица\n\n");
    PrintMatrix(singular, n);
    printf("\n");
    
    fclose(input);
    
    // Освобождение памяти
    for (int i = 0; i < n; ++i) {
        free(matrix[i]);
    }
    free(matrix);
    
    for (int i = 0; i < n; ++i) {
        free(singular[i]);
    }
    free(singular);
    return 0;
}
