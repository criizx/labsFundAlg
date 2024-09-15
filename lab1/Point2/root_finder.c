#include "root_finder.h"

double findRoot(double (*polinom)(double), double a, double b, double eps) {
    double c;
    while ((b - a) / 2 > eps) {
        c = (a + b) / 2;
        if (polinom(a) * polinom(c) > 0) {
            a = c;
        } else {
            b = c;
        }
    }
    return c;
}
