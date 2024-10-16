#include <float.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>

#include "errors.h"

ErrorCode geometricMean(int count, double* result, ...) {
	if (count <= 0) {
		return ERROR_INVALID_INPUT;
	}

	va_list args;
	va_start(args, result);

	double product = 1.0;
	for (int i = 0; i < count; i++) {
		double num = va_arg(args, double);
		if (num <= 0) {
			va_end(args);
			return ERROR_INVALID_INPUT;
		}

		if (product > DBL_MAX / num) {
			va_end(args);
			return ERROR_OVERFLOW;
		}

		product *= num;
	}

	va_end(args);

	*result = pow(product, 1.0 / count);

	if (isnan(*result) || isinf(*result)) {
		return ERROR_OVERFLOW;
	}

	return SUCCESS;
}

ErrorCode power(double base, int exponent, double* result) {
	if (exponent == 0) {
		*result = 1.0;
		return SUCCESS;
	}

	if (exponent < 0) {
		ErrorCode res = power(base, -exponent, result);
		if (res != SUCCESS) {
			return res;
		}

		if (*result == 0.0) {
			return ERROR_OVERFLOW;
		}

		*result = 1.0 / *result;
		return SUCCESS;
	}

	double halfResult;
	ErrorCode res = power(base, exponent / 2, &halfResult);
	if (res != SUCCESS) {
		return res;
	}

	if (halfResult > DBL_MAX / halfResult) {
		return ERROR_OVERFLOW;
	}

	if (exponent % 2 == 0) {
		*result = halfResult * halfResult;
	} else {
		if (base > DBL_MAX / (halfResult * halfResult)) {
			return ERROR_OVERFLOW;
		}
		*result = base * halfResult * halfResult;
	}

	return SUCCESS;
}

int main() {
	int count = 3;
	double geomResult;
	ErrorCode geomStatus = geometricMean(count, &geomResult, 1.0, 2.0, 3.0);

	if (geomStatus == SUCCESS) {
		printf("Geometric mean: %.4f\n", geomResult);
	} else {
		handleError(geomStatus);
	}

	double base = 2.0;
	int exponent = 3;
	double powerResult;
	ErrorCode powerStatus = power(base, exponent, &powerResult);

	if (powerStatus == SUCCESS) {
		printf("%.2f raised to the power of %d = %.4f\n", base, exponent, powerResult);
	} else {
		handleError(powerStatus);
	}

	return 0;
}
