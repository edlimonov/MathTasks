#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 1. Назовем весом столбца матрицы число, равное сумме модулей разностей соседних
 элементов этого столбца, т.е. |a[i][j] - а[i+1][j]| для і=0,..., N-2.
 В матрице должно присутствовать хотя бы два столбца. Требуется переставить столбцы матрицы так, чтобы они стояли по убыванию (невозрастанию) своих весов
 (при возрастании номера столбца).
 */

int GetMem(double ***matrix, int n, int m){
    
    *matrix = (double **)malloc(n * sizeof(double *));
    
    if (matrix == NULL){
        //Fail to allocate mem
        return 1;
    }
    
    for (int i = 0; i < n; ++i){
        *matrix[i] = (double *)malloc(m * sizeof(double));
        if (matrix[i] == NULL){
            //Fail to allocate mem
            return 1;
        }
    }
    
    return 0;
}

int Input (FILE *input, double ***matrix, int n, int m){
    
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            if (fscanf(input, "%lf", matrix[i][j])) return 1;
        }
    }
    
    return 0;
}

int f(double ***matrix, int n, int j){
    
    int sum = 0;
    
    for (int i = 0; i < n-1; ++i){
        sum += fabs(*matrix[i][j] - *matrix[i+1][j]);
    }
    
    return sum;
}

void Swap (double ***matrix, int n, int j){
    
    for (int i = 0; i < n; ++i){
        double tmp = *matrix[i][j];
        *matrix[i][j] = *matrix[i][j+1];
        *matrix[i][j+1] = tmp;
    }
    
}

void Sort(double ***matrix, int n, int m){
    
    for (int i = 0; i < m-1; ++i){
        for (int j = 0; j < m-i-1; ++j){
            if (f(matrix, n, j) < f(matrix, n, j+1)){
                Swap(matrix, n, j);
                }
            }
        }
    
}

void Print (FILE *output, double ***matrix, int n, int m){
    
    fprintf(output, "%d %d\n", n, m);
    
    for (int i = 0; i < 0; ++i){
        for (int j = 0; j < m; ++j){
            fprintf(output, "%lf ", *matrix[i][j]);
        }
        fprintf(output, "\n");
    }
    
    fprintf(output, "\n");
    
    for (int i = 0; i < n; ++i){
        
        double sum = 0;
        
        for (int j = 0; j < m; ++j){
            sum += *matrix[i][j] * *matrix[1][j];
        }
        fprintf(output, "%lf ", sum);
    }
    
}

int main(void) {
    
    //Проверка файлов
    FILE *input = fopen("/Users/nailzaripov/Desktop/input.txt", "r");
    if(input == NULL) return -1;
    
    FILE *output = fopen("/Users/nailzaripov/Desktop/output.txt", "w");
    if(output == NULL){
        fclose(input);
        return -1;
    }
    
    //Матрица
    double **matrix;
    
    //Размерность
    int n = 0, m = 0;
    int tmp1 = fscanf(input, "%d", &n);
    int tmp2 = fscanf(input, "%d", &m);
    
    if (tmp1 + tmp2 < 2 || m < 2){
        fclose(input);
        fclose(output);
        return -1;
    }
    
    if (GetMem(&matrix, n, m) || Input(input, &matrix, n, m)){
        fclose(input);
        fclose(output);
        return -1;
    }
    
    fclose(input);
    
    Sort(&matrix, n, m);
    Print(output, &matrix, n, m);
    
    for (int i = 0; i < n; ++i){
        free(matrix[i]);
    }
    
    free(matrix);
    fclose(output);
    
    return 0;
}
