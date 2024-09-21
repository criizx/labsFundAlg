#include <stdio.h>
#include <math.h>
#include "polynomials.h"

double trapezoidal(double (*f)(double), double a, double b, int n){
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));

    for (int i = 1; i < n; ++i){
        double x = a + i * h;
        sum += f(x);
    }

    return sum * h;
}

double integrateWithPrecision(double (*func)(double), double a, double b, double precision){
    int n = 10; // начальное кол-во шагов
    double prevRes, currentRes;

    prevRes = trapezoidal(func, a, b, n);

    do {
        n *= 2;
        currentRes = trapezoidal(func, a, b, n);
    } while (fabs(currentRes - prevRes) > precision);

    return currentRes;
}

int main(int argc, char *argv[]){
    double a = 0.000001;
    double b = 1.0;
    double precision;
    char choice;

    printf("choose func for integrating:\n");
    printf("a. ln(x + 1) / x\n");
    printf("b. e^-(x^2 / 2)\n");
    printf("c. 1/(1-x)\n");
    printf("d. x^x\n");
    scanf("%c", &choice);

    printf("enter precision\n");
    scanf("%lf", &precision);

    double (*func)(double);

    switch (choice)
    {
    case 'a':
        func = typeA;
        break;
    case 'b':
        func = typeB;
        break;
    case 'c':
        func = typeC;
        break;
    case 'd':
        func = typeD;
        break;
    
    default:
        printf("incorrect choice");
        return 1;
    }

    double result = integrateWithPrecision(func, a, b, precision);

    printf("%.10lf", result);
}