#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

int gcd(int a, int b) {
	while (b != 0) {
		int temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

bool hasFiniteRepresentationInBase(double number, int base) {
	if (number <= 0.0 || number >= 1.0) {
		printf("Error: Number out of range (0, 1)\n");
		return false;
	}

	int denom = 1;
	while (fmod(number, 1.0) != 0.0) {
		number *= 10;
		denom *= 10;
	}
	int numerator = (int)number;

	int divisor = gcd(numerator, denom);
	numerator /= divisor;
	denom /= divisor;

	for (int i = 2; i <= base; i++) {
		if (base % i == 0) {
			while (denom % i == 0) {
				denom /= i;
			}
		}
	}
	return denom == 1;
}

void checkFiniteRepresentationInBase(int base, int count, ...) {
	va_list args;
	va_start(args, count);

	for (int i = 0; i < count; i++) {
		double num = va_arg(args, double);

		if (hasFiniteRepresentationInBase(num, base)) {
			printf("The number %.10f has a finite representation in base %d.\n", num, base);
		} else {
			printf("The number %.10f does not have a finite representation in base %d.\n", num, base);
		}
	}

	va_end(args);
}

int main() {
	checkFiniteRepresentationInBase(8, 8, 0.25, 0.333, 0.75, 0.111);
	return 0;
}
