#include <stdio.h>
#include <math.h>
#include "error_codes.h"
#include "functions.h"

unsigned long long Factorial(int n) {
	if (n < 0) {
		printf("There is no factorial for negative numbers\n");
		return 0;
	}
	if (n == 0 || n == 1){
		return 1;
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
