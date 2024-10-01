#include "functions.h"

#include <math.h>
#include <stdio.h>

void print_quadratic_result(int num_roots, double root1, double root2) {
	if (num_roots == 0) {
		printf("No real roots.\n");
	} else if (num_roots == 1) {
		printf("One root: %lf\n", root1);
	} else if (num_roots == 2) {
		printf("Two roots: %lf, %lf\n", root1, root2);
	}
}

int solve_quadratic(double epsilon, double a, double b, double c, double* root1, double* root2) {
	double discriminant = b * b - 4 * a * c;

	if (fabs(discriminant) < epsilon) {
		discriminant = 0.0;
	}

	if (discriminant < 0) {
		return 0;
	} else if (discriminant == 0) {
		*root1 = -b / (2 * a);
		return 1;
	} else {
		double sqrt_discriminant = sqrt(discriminant);
		*root1 = (-b + sqrt_discriminant) / (2 * a);
		*root2 = (-b - sqrt_discriminant) / (2 * a);
		return 2;
	}
}

int check_multiple(int num1, int num2) {
	if (num2 == 0) {
		printf("Cannot divide by zero.\n");
		return;
	}
	return num1 % num2;
}

int check_triangle(double epsilon, double a, double b, double c) {
	double max_side = fmax(fmax(a, b), c);
	double sum_of_squares = a * a + b * b + c * c - max_side * max_side;
	double max_side_square = max_side * max_side;

	return fabs(sum_of_squares - max_side_square) < epsilon;
}
