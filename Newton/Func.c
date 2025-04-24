#include <math.h>
#include <float.h>
#include <stdio.h>
#define EPS 1e-2

//Подинтегральная функция
double f(double x){
    double res = (cos(x) + 1)/pow(x, 1./3);
    return res;
}

//Первообразная в окрестности нуля
double F(double x){
    double res = -3./16 * pow(x, 8./3) + 3 * pow(x, 2./3);
    return res;
}

//Интеграл
double Int(double x){
    
    double start = 0.1;
    double integral = 0;
    double integral_new = 0;
    int number = 10000;
    
    if (x < 0.1){
        return F(x) - F(0);
    } else {
        
        do {
            
            integral = integral_new;
            integral_new = 0;
            
            //Шаг разбиения
            double step = (x-start)/number;
            
            for (int i = 0; i < number; i++){
                integral_new += step*f(start+i*step);
            }
            
            number *= 2;
            
        } while (fabs(integral_new - integral) > EPS);
        
        integral_new += F(0.1) - F(0);
    }
    
    return integral_new;
}

double Fun(double x, double alpha){
    return Int(x)-alpha;
}

