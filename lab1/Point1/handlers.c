#include "handlers.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error_codes.h"
#include "functions.h"

int HandlerOptH(int input_num) {
	if (input_num <= 0 || input_num > 100) {
		printf("There is not a single natural number that is a multiple of %d in the range from 1 to 100\n", input_num);
		return E_OUT_OF_RANGE;
	}
	for (int i = 1; i <= 100; ++i) {
		if (i % input_num == 0) {
			printf("%d\n", i);
		}
	}
	return S_OK;
}

int HandlerOptP(int input_num) {
	if (input_num < 0) {
		printf("Number must be positive for prime check\n");
		return E_OUT_OF_RANGE;
	}
	if (IsPrime(input_num)) {
		printf("%d is prime number\n", input_num);
	} else {
		printf("%d is composite number\n", input_num);
	}
	return S_OK;
}

int HandlerOptS(int input_num) {
	DecToHex(input_num);
	return S_OK;
}

int HandlerOptE(int input_num) {
	if (input_num >= 10) {
		printf("Input number is bigger than 10\n");
		return E_OUT_OF_RANGE;
	}
	printf("base | ");
	for (int i = 1; i <= input_num; i++) {
		printf("degree %d | ", i);
	}
	printf("\n");
	for (int base = 1; base <= 10; base++) {
		printf("%9d | ", base);
		for (int exp = 1; exp <= input_num; exp++) {
			printf("%9.0f | ", pow(base, exp));
		}
		printf("\n");
	}
	return S_OK;
}

int HandlerOptA(int input_num) {
	printf("%d", SumUpToN(input_num));
	return S_OK;
}

int HandlerOptF(int input_num) {
	unsigned long long result = Factorial(input_num);
	if (result == E_CALCULATION_OVERFLOW) {
		return E_CALCULATION_OVERFLOW;
	}
	printf("%llu\n", result);
	return S_OK;
}
