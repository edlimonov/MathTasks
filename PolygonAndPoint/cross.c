#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "struct.h"
#include <math.h>
//Проверка пересечения
int cross(struct point_2d *array, int len, struct point_2d P, FILE *input, FILE *output){

    while (true){
        
        double eps = 1/pow(2, 30);
        int cross_p = 0;
        int count = 0;
        double k = (double)rand()/(double)rand();
        double b = P.y - k*P.x;
        
        //Идем по массиву точек
        for (int i = 0; i < len; i++){
            
            //Вертикальный отрезок
            if (fabs(array[i].x - array[i+1].x) < eps){
                
                //Точка лежит на границе
                if ((fabs(P.x - array[i].x)<eps) && ((P.y >= array[i].y && P.y <= array[i+1].y) || (P.y <= array[i].y && P.y >= array[i+1].y))){
                    fprintf(output, "Точка лежит на границе");
                    fclose(input);
                    fclose(output);
                    return -1;
                }
                
                //Луч проходит через границу отрезка
                if ((fabs(k*array[i].x + b - array[i].y)<eps) || (fabs(k*array[i].x + b - array[i+1].y))){
                    break;
                }
                
                //Луч пересекает отрезок
                if (((k*array[i].x + b < array[i].y) && (k*array[i].x + b > array[i+1].y)) || ((k*array[i].x + b < array[i].y) && (k*array[i].x + b > array[i+1].y))){
                    ++cross_p;
                }
                
                ++count;
            }
            
            //Наклонный отрезок
            else{
                
                double kef_k = (array[i+1].y - array[i].y)/(array[i+1].x - array[i].x);
                double kef_b = array[i+1].y - kef_k*array[i+1].x;
                
                //Точка лежит на границе
                if ((fabs(P.y - kef_k*P.x + kef_b)<eps) && (((P.y >= array[i].y) && (P.y <= array[i+1].y)) || ((P.y <= array[i].y) && (P.y >= array[i+1].y)))){
                    fprintf(output, "Точка лежит на границе");
                    fclose(input);
                    fclose(output);
                    return -1;
                }
                
                //Луч совпадает с отрезком
                if ((fabs(kef_k - k)<eps) && (fabs(kef_b - b)<eps)){
                    break;
                }

                //Прямые пересекаются
                if (fabs(kef_k - k)>eps){
                    //Луч проходит через границу отрезка
                    if ((fabs((b - kef_b)/(kef_k - k) - array[i+1].x)<eps) || (fabs((b - kef_b)/(kef_k - k) - array[i].x)<eps)){
                        break;
                    }
                    //Луч пересекает отрезок
                    if ((((b - kef_b)/(kef_k - k) > array[i].x) && ((b - kef_b)/(kef_k - k) < array[i].x)) || (((b - kef_b)/(kef_k - k) < array[i].x) && ((b - kef_b)/(kef_k - k) > array[i].x))){
                        ++cross_p;
                    }
                }
                ++count;
            }
        }
        //Проверка, что прошли по всем отрезкам
        if (count == len){
            return cross_p;
        }
    }
}
