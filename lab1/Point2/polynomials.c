#include "polynomials.h"
#include "functions.h"
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

// Polynomial functions for equations
double polinomE(double x, double precision) {
	return log(x) - 1;
}

double polinomPi(double x, double precision) {
	return sin(x / 180);
}

double polinomLn2(double x, double precision) {
	return exp(x) - 2;
}

double polinomSqrt2(double x, double precision) {
	return x * x - 2;
}

double findEulerMascheroniLimit(double precision) {
	double x = 10 / precision;

	bool *is_prime = (bool *)malloc((x + 1) * sizeof(bool));
	if (!is_prime) {
		exit(1);  // Memory allocation failed
	}
	
	sieve_of_eratosthenes(x, is_prime);
	double product = 1.0;
	for (int p = 2; p <= x; p++) {
		if (is_prime[p]) {
			product *= (1.0 - 1.0 / p);
		}
	}
	free(is_prime);
	
	return log(x) * product;
}

double polinomEulerMascheroni(double x, double precision) {
	double lim = findEulerMascheroniLimit(precision);
	return exp(-x) - lim;
}
