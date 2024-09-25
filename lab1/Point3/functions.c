#include "functions.h"

#include <math.h>
#include <stdio.h>

void solve_quadratic(double epsilon, double a, double b, double c) {
	double discriminant = b * b - 4 * a * c;
	if (fabs(discriminant) < epsilon) {
		discriminant = 0.0;
	}

	if (discriminant < 0) {
		printf("No real roots.\n");
	} else if (discriminant == 0) {
		double x = -b / (2 * a);
		printf("One root: %lf\n", x);
	} else {
		double sqrt_discriminant = sqrt(discriminant);
		double x1 = (-b + sqrt_discriminant) / (2 * a);
		double x2 = (-b - sqrt_discriminant) / (2 * a);
		printf("Two roots: %lf, %lf\n", x1, x2);
	}
}

void check_multiple(int num1, int num2) {
	if (num2 == 0) {
		printf("Cannot divide by zero.\n");
		return;
	}

	if (num1 % num2 == 0) {
		printf("%d is a multiple of %d.\n", num1, num2);
	} else {
		printf("%d is not a multiple of %d.\n", num1, num2);
	}
}

void check_triangle(double epsilon, double a, double b, double c) {
	double max_side = fmax(fmax(a, b), c);
	double sum_of_squares = a * a + b * b + c * c - max_side * max_side;
	double max_side_square = max_side * max_side;

	if (fabs(sum_of_squares - max_side_square) < epsilon) {
		printf("The numbers form a right triangle.\n");
	} else {
		printf("The numbers do not form a right triangle.\n");
	}
}
