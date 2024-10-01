#include <math.h>
#include <stdio.h>

#include "error_codes.h"
#include "functions.h"

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
		currentSum += pow(-1, n) * pow(x, 2 * n) / Factorial(2 * n);
		n++;
	} while (fabs(prevSum - currentSum) > precision);
	printf("Result of sum B: %f\n", currentSum);
	return S_OK;
}

int HandlerOptc(double precision, double x) {
	long double prevSum = 0.0;
	long double currentSum = 0.0;
	int n = 0;
	do {
		prevSum = currentSum;
		if (Factorial(3 * n) == E_CALCULATION_OVERFLOW) {
			return E_CALCULATION_OVERFLOW;
		}
		currentSum += (pow(3, 3 * n) * pow(Factorial(n), 3) * pow(x, 2 * n)) / Factorial(3 * n);
		n++;
	} while (fabs(prevSum - currentSum) > precision);
	printf("Result of sum C: %Lf\n", currentSum);
	return S_OK;
}

int HandlerOptd(double precision, double x) {
	long double prevSum = 0.0;
	long double currentSum = 0.0;
	int n = 1;
	do {
		prevSum = currentSum;
		long double res = 1.0;
		for (int i = 1; i <= 2 * n; ++i) {
			int chet = i % 2;
			switch (chet) {
				case 1:
					res *= i;
					break;
				case 0:
					res /= i;
					break;
			}
		}
		currentSum += pow(-1, n) * pow(x, 2 * n) * res;
		n++;
	} while (fabs(prevSum - currentSum) > precision);
	printf("Result of sum D: %Lf\n", currentSum);
	return S_OK;
}
