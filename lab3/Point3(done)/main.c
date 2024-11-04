#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "employee.h"

#define PATH_MAX 1024

int main(int argc, char *argv[]) {
	if (argc != 4) {
		printf("Usage: %s <input_file> <flag> <output_file>\n", argv[0]);
		return 1;
	}

	const char *inputFile = argv[1];
	const char *flag = argv[2];
	const char *outputFile = argv[3];

	char *absInputFile = malloc(PATH_MAX);
	if (!absInputFile) {
		printf("Memory allocation error for input file path\n");
		return 1;
	}
	char *absOutputFile = malloc(PATH_MAX);
	if (!absOutputFile) {
		printf("Memory allocation error for output file path\n");
		free(absInputFile);
		return 1;
	}

	if (!realpath(inputFile, absInputFile)) {
		printf("Error resolving path for input file: %s\n", inputFile);
		free(absInputFile);
		free(absOutputFile);
		return 1;
	}
	if (!realpath(outputFile, absOutputFile)) {
		printf("Error resolving path for output file: %s\n", outputFile);
		free(absInputFile);
		free(absOutputFile);
		return 1;
	}

	if (strcmp(absInputFile, absOutputFile) == 0) {
		printf("Error: Input and output files are the same.\n");
		free(absInputFile);
		free(absOutputFile);
		return 1;
	}

	free(absInputFile);
	free(absOutputFile);

	int ascending;
	if (strcmp(flag, "-a") == 0 || strcmp(flag, "/a") == 0) {
		ascending = 1;
	} else if (strcmp(flag, "-d") == 0 || strcmp(flag, "/d") == 0) {
		ascending = 0;
	} else {
		printf("Invalid flag. Use '-a' or '-d'.\n");
		return 1;
	}

	Employee *employees = NULL;
	int count = 0;
	int result = readEmployees(inputFile, &employees, &count);
	if (result != 0) {
		if (result == -1) {
			printf("Error opening input file\n");
		} else if (result == -2) {
			printf("Memory allocation error\n");
		} else if (result == -3) {
			printf("Error allocating memory for names\n");
		}
		return 1;
	}

	result = sortEmployees(employees, count, ascending);
	if (result != 0) {
		printf("Error sorting employees\n");
		freeEmployees(employees, count);
		return 1;
	}

	result = writeEmployees(outputFile, employees, count);
	if (result != 0) {
		printf("Error opening output file\n");
		freeEmployees(employees, count);
		return 1;
	}

	freeEmployees(employees, count);
	return 0;
}
