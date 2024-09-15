#include <math.h>
#include "polynomials.h"

double polinomE(double x) {
    return exp(x) - 2;
}

double polinomPi(double x) {
    return cos(x) + 1;
}

double polinomLn2(double x) {
    return pow(exp(x), x) - 2;
}

double polinomSqrt2(double x) {
    return x * x - 2;
}
