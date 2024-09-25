#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdbool.h>

void sieve_of_eratosthenes(int x, bool *is_prime);
double FactorialLog(int n);
unsigned long long BinomialCoefficient(int n, int k);
double CalculateELimit(double precision);
double CalculateESeries(double precision);
double CalculatePiLimit(double precision);
double CalculatePiSeries(double precision);
double CalculateLn2Limit(double precision);
double CalculateLn2Series(double precision);
double CalculateSqr2Limit(double precision);
double CalculateSqr2Series(double precision);
double CalculateYLimit(double precision);
double CalculateYSeries(double precision);
double CalculateRootUsingEquation(double (*func)(double, double), double low, double high, double precision);

#endif
