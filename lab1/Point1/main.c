#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "handlers.h"
#include "error_codes.h"

typedef enum KOpts {
	kOptH,
	kOptP,
	kOptS,
	kOptE,
	kOptA,
	kOptF
} KOpts;

int GetOpts(int argc, char** argv, KOpts* option, int* number) {
	if (argc != 3) {
		printf("Invalid number of arguments\nExpected: 2 arguments\n");
		return E_OUT_OF_RANGE;
	}

	char* endptr;
	*number = strtol(argv[1], &endptr, 10);
	if (*endptr != '\0') {
		printf("Invalid input format: %s is not a valid number\n", argv[1]);
		return E_INVALID_FORMAT;
	}

	if (strcmp(argv[2], "-h") == 0) {
		*option = kOptH;
	} else if (strcmp(argv[2], "-p") == 0) {
		*option = kOptP;
	} else if (strcmp(argv[2], "-s") == 0) {
		*option = kOptS;
	} else if (strcmp(argv[2], "-e") == 0) {
		*option = kOptE;
	} else if (strcmp(argv[2], "-a") == 0) {
		*option = kOptA;
	} else if (strcmp(argv[2], "-f") == 0) {
		*option = kOptF;
	} else {
		printf("Unknown option: %s\n", argv[2]);
		return E_UNKNOWN_OPT;
	}

	return S_OK;
}

int main(int argc, char* argv[]) {
	KOpts opt = kOptH;
	int processed_number = 0;

	void (*handlers[6])(int) = {
		HandlerOptH, HandlerOptP, HandlerOptS,
		HandlerOptE, HandlerOptA, HandlerOptF
	};

	int error_code = GetOpts(argc, argv, &opt, &processed_number);
	if (error_code != S_OK) {
		printf("Error occurred: %d\n", error_code);
		return error_code;
	}

	handlers[opt](processed_number);

	return S_OK;
}
