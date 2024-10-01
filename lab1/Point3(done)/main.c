#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "handlers.h"

typedef enum { kOptQ, kOptM, kOptT, kOptUnknown } KOpts;

int GetOpts(int argc, char** argv, KOpts* option, int* args_count, double* args) {
	if (argc < 2) {
		printf("Error: No flag provided.\n");
		return ARG_ERROR;
	}

	if (strcmp(argv[1], "-q") == 0) {
		*option = kOptQ;
		*args_count = 4;
	} else if (strcmp(argv[1], "-m") == 0) {
		*option = kOptM;
		*args_count = 2;
	} else if (strcmp(argv[1], "-t") == 0) {
		*option = kOptT;
		*args_count = 4;
	} else {
		*option = kOptUnknown;
		return FLAG_ERROR;
	}

	if (argc != *args_count + 2) {
		printf("Error: Invalid number of arguments for %s flag.\n", argv[1]);
		return ARG_ERROR;
	}

	for (int i = 0; i < *args_count; i++) {
		args[i] = atof(argv[i + 2]);
	}

	return SUCCESS;
}

int main(int argc, char* argv[]) {
	KOpts opt = kOptUnknown;
	int args_count = 0;
	double args[4] = {0};

	int (*handlers[])(double*) = {HandleOptQ, HandleOptM, HandleOptT};

	int error_code = GetOpts(argc, argv, &opt, &args_count, args);
	if (error_code != SUCCESS) {
		printf("Error occurred: %d\n", error_code);
		return error_code;
	}

	if (opt != kOptUnknown) {
		error_code = handlers[opt](args);
		if (error_code != SUCCESS) {
			printf("Handler error: %d\n", error_code);
			return error_code;
		}
	} else {
		printf("Error: Unknown option provided.\n");
		return FLAG_ERROR;
	}

	return SUCCESS;
}
