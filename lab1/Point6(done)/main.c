#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "polynomials.h"

double CalculateRootUsingEquation(double low, double high, double precision) {
	double mid;

	while ((high - low) > precision) {
		mid = (low + high) / 2.0;

		if (typeC(mid, precision) == 0.0) {
			return mid;
		} else if (typeC(mid, precision) * typeC(low, precision) < 0) {
			high = mid;
		} else {
			low = mid;
		}
	}

	return mid;
}

double compute(double precision) {
	double prevRes = 0;
	double currRes = 0;
	int n = 1;
	do {
		prevRes = currRes;
		currRes += pow(-1, n - 1) / pow(n, n);
		n++;
	} while (fabs(currRes - prevRes) > precision);
	return currRes;
}

double trapezoidal(double (*f)(double), double a, double b, int n) {
	double h = (b - a) / n;
	double sum = 0.5 * (f(a) + f(b));

	for (int i = 1; i < n; ++i) {
		double x = a + i * h;
		sum += f(x);
	}

	return sum * h;
}

double integrateWithPrecision(double (*func)(double), double a, double b, double precision) {
	int n = 10;
	double prevRes, currentRes;

	prevRes = trapezoidal(func, a, b, n);

	do {
		n += 10;
		currentRes = trapezoidal(func, a, b, n);
	} while (fabs(currentRes - prevRes) > precision);

	return currentRes;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s <precision>\n", argv[0]);
		return 1;
	}

	double precision = atof(argv[1]);
	double a = 0.000001;
	double b = 1.0;

	char choice;

	printf("Choose func for integrating:\n");
	printf("a. ln(x + 1) / x\n");
	printf("b. e^-(x^2 / 2)\n");
	printf("c. ln 1/(1-x)\n");
	printf("d. x^x\n");

	double result1 = integrateWithPrecision(typeA, a, b, precision);
	printf("Result of integration for typeA: %.10lf\n", result1);

	double result2 = integrateWithPrecision(typeB, a, b, precision);
	printf("Result of integration for typeB: %.10lf\n", result2);

	double result3 = CalculateRootUsingEquation(a, b, precision);
	printf("Root found: %.10lf\n", result3);

	double result4 = compute(precision);
	printf("Computed value: %.10lf\n", result4);

	return 0;
}
