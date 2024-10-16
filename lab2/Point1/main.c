#include <stdio.h>
#include <stdlib.h>

#include "error_codes.h"
#include "handlers.h"
#include "utils.h"

typedef enum KOpts { kOptL, kOptR, kOptU, kOptN, kOptC } KOpts;

int getOpts(int argc, char** argv, KOpts* option, unsigned int* number) {
	if (argc < 2) {
		printf("No option flag provided.\n");
		return E_OUT_OF_RANGE;
	}

	if (myStrcmp(argv[1], "-c") == 0) {
		if (argc < 4) {
			printf(
			    "Invalid number of arguments for -c flag\nExpected: at least 3 arguments (flag, number, and one or "
			    "more strings)\n");
			return E_OUT_OF_RANGE;
		}
		*option = kOptC;

		char* endptr;
		*number = strtoul(argv[2], &endptr, 10);
		if (*endptr != '\0') {
			printf("Invalid input format: %s is not a valid number\n", argv[2]);
			return E_INVALID_FORMAT;
		}
	} else {
		if (argc != 3) {
			printf("Invalid number of arguments for %s flag\nExpected: 2 arguments (flag and string)\n", argv[1]);
			return E_OUT_OF_RANGE;
		}

		if (myStrcmp(argv[1], "-l") == 0) {
			*option = kOptL;
		} else if (myStrcmp(argv[1], "-r") == 0) {
			*option = kOptR;
		} else if (myStrcmp(argv[1], "-u") == 0) {
			*option = kOptU;
		} else if (myStrcmp(argv[1], "-n") == 0) {
			*option = kOptN;
		} else {
			printf("Unknown option: %s\n", argv[1]);
			return E_UNKNOWN_OPT;
		}
	}

	return S_OK;
}

int main(int argc, char* argv[]) {
	KOpts opt;
	unsigned int number = 0;

	int errorCode = getOpts(argc, argv, &opt, &number);
	if (errorCode != S_OK) {
		printf("Error occurred: %d\n", errorCode);
		return errorCode;
	}

	if (opt == kOptC) {
		HandlerOptC(number, argc - 3, &argv[3]);
	} else {
		switch (opt) {
			case kOptL: {
				int length = HandlerOptL(argv[2]);
				if (length < 0) {
					printf("Error: Invalid string input.\n");
					return E_INVALID_FORMAT;
				}
				printf("Length of the string: %d\n", length);
				break;
			}
			case kOptR: {
				char* reversedStr = HandlerOptR(argv[2]);
				if (reversedStr != NULL) {
					printf("Reversed string: %s\n", reversedStr);
					free(reversedStr);
				} else {
					printf("Memory allocation error.\n");
					return E_MEM_ALLOC_FAILED;
				}
				break;
			}
			case kOptU: {
				char* updatedStr = HandlerOptU(argv[2]);
				if (updatedStr != NULL) {
					printf("Updated string: %s\n", updatedStr);
					free(updatedStr);
				} else {
					printf("Memory allocation error.\n");
					return E_MEM_ALLOC_FAILED;
				}
				break;
			}
			case kOptN: {
				char* sortedStr = HandlerOptN(argv[2]);
				if (sortedStr != NULL) {
					printf("Sorted string: %s\n", sortedStr);
					free(sortedStr);
				} else {
					printf("Memory allocation error.\n");
					return E_MEM_ALLOC_FAILED;
				}
				break;
			}
		}
	}

	return S_OK;
}