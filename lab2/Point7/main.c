#include <math.h>
#include <stdio.h>

double f(double x) { return x - 1; }

double dichotomy(double (*func)(double), double a, double b, double epsilon) {
	double midPoint;
	while ((b - a) >= epsilon) {
		midPoint = (a + b) / 2;

		if (func(midPoint) == 0.0) {
			return midPoint;
		} else if (func(midPoint) * func(a) < 0) {
			b = midPoint;
		} else {
			a = midPoint;
		}
	}
	return midPoint;
}

int main() {
	double a = -1.0, b = 4.0, epsilon = 0.0001;
	double root = dichotomy(f, a, b, epsilon);

	if (root != -1) {
		printf("Root found: %lf\n", root);
	} else {
		printf("Failed to find root due to an error.\n");
	}

	return 0;
}
