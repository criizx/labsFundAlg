#include <math.h>

double typeA(double x) { return log(x + 1) / x; }

double typeB(double x) { return exp(-pow(x, 2) / 2); }

double typeC(double x, double precision) { return x + log(1 - x) * (1 - x); }