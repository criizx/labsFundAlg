#include <math.h>

double typeA(double x){
    return log(x + 1) / x;
}

double typeB(double x){
    return exp(-pow(x, 2) / 2);
}

double typeC(double x){
    return log(1/(1 - x));
}

double typeD(double x){
    return pow(x, x);
}