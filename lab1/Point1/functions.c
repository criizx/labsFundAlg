#include "functions.h"

#include <math.h>
#include <stdio.h>

#include "error_codes.h"

#define HEX_SIZE 100

void DecToHex(int n) {
	if (n < 0) {
		printf("Number must be non-negative for hex conversion\n");
		return;
	}

	if (n >= HEX_SIZE) {
		printf("Number too large to be converted to hex\n");
		return;
	}

	char hex[HEX_SIZE];
	int i = 0;

	if (n == 0) {
		printf("0");
		return;
	}

	while (n != 0) {
		int remainder = n % 16;
		if (remainder < 10) {
			hex[i] = remainder + '0';
		} else {
			hex[i] = remainder - 10 + 'A';
		}
		n /= 16;
		i++;
	}

	for (int j = i - 1; j >= 0; j--) {
		printf("%c ", hex[j]);
	}
	printf("\n");
}

int SumUpToN(int n) {
	int result = 0;
	for (int i = 1; i <= n; ++i) {
		result += i;
	}
	return result;
}

unsigned long long Factorial(int n) {
	if (n < 0) {
		printf("There is no factorial for negative numbers\n");
		return 0;
	}
	unsigned long long result = 1;
	for (int i = 2; i <= n; ++i) {
		result *= i;

		if (result < 0) {
			printf("Factorial overflow for %d\n", n);
			return E_CALCULATION_OVERFLOW;
		}
	}
	return result;
}

int IsPrime(int num_for_check) {
	if (num_for_check < 2) {
		return 0;
	}
	int max_val = sqrt(num_for_check);
	for (int i = 2; i <= max_val; ++i) {
		if (num_for_check % i == 0) {
			return 0;
		}
	}
	return 1;
}
