#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double crossProduct(double x1, double y1, double x2, double y2, double x3, double y3) {
	return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
}

int isConvexPolygon(int numPoints, ...) {
	if (numPoints < 3) {
		printf("Error: Not enough vertices for a polygon\n");
		return 0;
	}

	va_list args;
	va_start(args, numPoints);

	double* x = malloc(numPoints * sizeof(double));
	double* y = malloc(numPoints * sizeof(double));

	if (!x || !y) {
		printf("Error: Memory allocation failed\n");
		return 0;
	}

	for (int i = 0; i < numPoints; i++) {
		x[i] = va_arg(args, double);
		y[i] = va_arg(args, double);
	}

	va_end(args);

	int sign = 0;
	for (int i = 0; i < numPoints; i++) {
		double cross = crossProduct(x[i], y[i], x[(i + 1) % numPoints], y[(i + 1) % numPoints], x[(i + 2) % numPoints],
		                            y[(i + 2) % numPoints]);
		if (cross != 0) {
			if (sign == 0)
				sign = (cross > 0) ? 1 : -1;
			else if ((cross > 0 && sign < 0) || (cross < 0 && sign > 0)) {
				free(x);
				free(y);
				return 0;
			}
		}
	}

	free(x);
	free(y);
	return 1;
}

double evaluatePolynomial(double x, int n, ...) {
	if (n < 0) {
		printf("Error: Polynomial degree must be non-negative\n");
		return 0;
	}

	va_list args;
	va_start(args, n);

	double result = 0;
	for (int i = 0; i <= n; i++) {
		double coeff = va_arg(args, double);
		result += coeff * pow(x, n - i);
	}

	va_end(args);
	return result;
}

int isKaprekar(int num) {
	int square = num * num;
	char squareStr[20];
	sprintf(squareStr, "%d", square);

	int len = strlen(squareStr);
	for (int i = 1; i < len; i++) {
		char leftStr[20] = {0};
		char rightStr[20] = {0};
		strncpy(leftStr, squareStr, i);
		strcpy(rightStr, squareStr + i);

		int left = atoi(leftStr);
		int right = atoi(rightStr);

		if (right != 0 && left + right == num) {
			return 1;
		}
	}
	return 0;
}

void findKaprekar(int base, int numStrings, ...) {
	va_list args;
	va_start(args, numStrings);

	for (int i = 0; i < numStrings; i++) {
		const char* numStr = va_arg(args, const char*);
		int num = strtol(numStr, NULL, base);
		if (isKaprekar(num)) {
			printf("%s (%d) is a Kaprekar number\n", numStr, num);
		} else {
			printf("%s (%d) is not a Kaprekar number\n", numStr, num);
		}
	}

	va_end(args);
}

int main() {
	if (isConvexPolygon(4, 10.0, 0.0, 4.0, 0.0, 4.0, 4.0, 0.0, 4.0)) {
		printf("The polygon is convex\n");
	} else {
		printf("The polygon is not convex\n");
	}

	double x = 2.0;
	double result = evaluatePolynomial(x, 3, 2.0, 3.0, 4.0, 5.0);
	printf("The value of the polynomial is: %lf\n", result);

	findKaprekar(10, 3, "46", "55", "297");

	return 0;
}
