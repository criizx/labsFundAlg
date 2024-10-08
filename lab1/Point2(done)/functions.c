#include "functions.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define M_PI 3.14159265358979323846

void sieveOfEratosthenes(int n, bool *is_prime) {
	for (int i = 0; i <= n; i++) {
		is_prime[i] = true;
	}
	is_prime[0] = is_prime[1] = false;
	for (int p = 2; p * p <= n; p++) {
		if (is_prime[p]) {
			for (int i = p * p; i <= n; i += p) {
				is_prime[i] = false;
			}
		}
	}
}

double FactorialLog(int n) {
	double result = 0.0;
	for (int i = 1; i <= n; ++i) {
		result += log(i);
	}
	return result;
}

unsigned long long BinomialCoefficient(int n, int k) {
	unsigned long long result = 1;
	for (int i = 0; i < k; ++i) {
		result *= (n - i);
		result /= (i + 1);
	}
	return result;
}

// e calculation
double CalculateELimit(double precision) {
	double e_prev = 0.0;
	double e_current = 0.0;
	int n = 1;

	do {
		e_prev = e_current;
		e_current = pow(1.0 + 1.0 / n, n);
		n++;
	} while (fabs(e_current - e_prev) > precision);

	return e_current;
}

double CalculateESeries(double precision) {
	double e_prev = 1;
	double e_current = 2;
	int n = 2;
	do {
		double nFac = 1;
		for (int i = 1; i <= n; ++i) {
			nFac *= i;
		}
		e_prev = e_current;
		e_current += 1.0 / nFac;
		n++;
	} while (fabs(e_current - e_prev) > precision);

	return e_current;
}

// pi calculation
double CalculatePiLimit(double precision) {
	double piCurr = 4.0;
	double piPrev = 0;
	int n = 1;
	do {
		piPrev = piCurr;
		piCurr *= (4 * (n + 1) * n) / pow(2 * n + 1, 2);
		n++;
	} while (fabs(piCurr - piPrev) > precision);
	return piCurr;
}

double CalculatePiSeries(double precision) {
	double pi_current = 0.0;
	double pi_prev = 0.0;
	double term;
	int n = 1;

	do {
		pi_prev = pi_current;
		pi_current = pi_prev + pow(-1.0, n + 1) / (2.0 * n - 1.0);
		n++;
	} while (fabs(4 * pi_current - 4 * pi_prev) > precision);

	return pi_current * 4.0;
}

// ln2 calculation
double CalculateLn2Limit(double precision) {
	double ln2_prev = 0.0;
	double ln2_current = 0.0;
	int n = 1;

	do {
		ln2_prev = ln2_current;
		ln2_current = n * (pow(2, 1.0 / n) - 1);
		n++;
	} while (fabs(ln2_current - ln2_prev) > precision);

	return ln2_current;
}

double CalculateLn2Series(double precision) {
	double ln2_prev = 0;
	double ln2_current = 0;
	int n = 1;

	do {
		ln2_prev = ln2_current;
		ln2_current += pow(-1, n - 1) / n;
		n++;
	} while (fabs(ln2_current - ln2_prev) > precision);

	return ln2_current;
}

// sqr2 calculation
double CalculateSqr2Limit(double precision) {
	double sqr2_prev = -1000.0;
	double sqr2_current = -1000.0;
	double x = -0.5;

	do {
		sqr2_prev = sqr2_current;
		x = x - pow(x, 2.0) / 2.0 + 1.0;
		sqr2_current = x;
	} while (fabs(sqr2_current - sqr2_prev) > precision);

	return sqr2_current;
}

double CalculateSqr2Series(double precision) {
	double sqr2_prev = 1;
	double sqr2_current = pow(2.0, 0.25);
	double n = 3.0;

	do {
		sqr2_prev = sqr2_current;
		sqr2_current *= pow(2.0, pow(2.0, -n));
		n++;
	} while (fabs(sqr2_current - sqr2_prev) > precision);

	return sqr2_current;
}

// Y calculation
double CalculateYLimit(double precision) {
	double y_current = 1.0;
	double y_prev = 0.0;
	int m = 1;

	do {
		y_prev = y_current;
		y_current = 0.0;

		for (int k = 1; k <= m; ++k) {
			unsigned long long binom_coeff = BinomialCoefficient(m, k);
			double term = binom_coeff * (pow(-1.0, k) / k) * FactorialLog(k);
			y_current += term;
		}

		m++;
	} while (fabs(y_current - y_prev) > precision);

	return y_current;
}

double CalculateYSeries(double precision) {
	double yPrev = 0;
	double n = 3;
	precision = 0.0000000000001;
	double yCurr = 0.5;
	double sum = 0;
	do {
		yPrev = yCurr;
		sum = ((1.0 / pow(floor(sqrt(n)), 2)) - (1.0 / n));
		yCurr += sum;
		if (precision > sum) {
			yPrev = 0;
		}
		n++;
	} while (fabs(yCurr - yPrev) > precision);
	return (yCurr - (M_PI * M_PI / 6));
}

double CalculateRootUsingEquation(double (*func)(double, double), double low, double high, double precision) {
	double mid;

	while ((high - low) > precision) {
		mid = (low + high) / 2.0;

		if (func(mid, precision) == 0.0) {
			return mid;
		} else if (func(mid, precision) * func(low, precision) < 0) {
			high = mid;
		} else {
			low = mid;
		}
	}

	return mid;
}