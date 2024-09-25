#include <stdio.h>
#include <stdlib.h>

#include "error_codes.h"
#include "handlers.h"

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Usage: %s <precision> <x>\n", argv[0]);
		return E_INVALID_INPUT;
	}

	double precision = atof(argv[1]);
	double x = atof(argv[2]);

	if (precision <= 0) {
		printf("Precision must be greater than 0\n");
		return E_INVALID_INPUT;
	}

	int (*handlers[4])(double, double) = {HandlerOpta, HandlerOptb, HandlerOptc, HandlerOptd};

	for (int i = 0; i < 4; ++i) {
		int error_code = handlers[i](precision, x);
		if (error_code != S_OK) {
			printf("Error in handler %d: %d\n", i, error_code);
			return error_code;
		}
	}

	return S_OK;
}
