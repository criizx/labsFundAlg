#include <stdio.h>
#include <math.h>
#include "functions.h"
#include "error_codes.h"

int HandlerOpta(double precision, double x) {
    double prevSum = 0.0;
    double currentSum = 0.0;
    int n = 0;
    do {
        prevSum = currentSum;
        currentSum += pow(x, n) / Factorial(n);
        n++;
    } while (fabs(prevSum - currentSum) > precision);
    printf("Result of sum A: %f\n", currentSum);
    return S_OK;
}

int HandlerOptb(double precision, double x) {
    double prevSum = 0.0;
    double currentSum = 0.0;
    int n = 0;
    do {
        prevSum = currentSum;
        currentSum += pow(-1, n) * pow(x, 2*n) / Factorial(2 * n);
        n++;
    } while (fabs(prevSum - currentSum) > precision);
    printf("Result of sum B: %f\n", currentSum);
    return S_OK;
}

int HandlerOptc(double precision, double x) {
    double prevSum = 0.0;
    double currentSum = 0.0;
    int n = 0;
    do {
        prevSum = currentSum;
        currentSum += pow(3, 3 * n) * pow(Factorial(n), 3) * pow(x, 2*n) / Factorial(3 * n);
        n++;
    } while (fabs(prevSum - currentSum) > precision);
    printf("Result of sum C: %f\n", currentSum);
    return S_OK;
}

int HandlerOptd(double precision, double x) {
    double prevSum = 0.0;
    double currentSum = 0.0;
    int n = 1;
    do {
        prevSum = currentSum;
        currentSum += pow(-1, n) * Factorial(Factorial(2 * n - 1)) * pow(x, 2 * n) / Factorial(Factorial(2 * n));
        n++;
    } while (fabs(prevSum - currentSum) > precision);
    printf("Result of sum D: %f\n", currentSum);
    return S_OK;
}
