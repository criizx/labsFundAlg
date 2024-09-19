#include "polynomials.h"
#include <math.h>

// Polynomial functions for equations
double polinomE(double x) {
    return log(x) - 1;
}

double polinomPi(double x) {
    return sin(x);
}

double polinomLn2(double x) {
    return exp(x) - 2;
}

double polinomSqrt2(double x) {
    return x * x - 2;
}

double polinomEulerMascheroni(double x) {
    return x - log(x);
}
