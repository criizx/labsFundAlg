#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "functions.h"

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Error: No flag provided.\n");
		return ARG_ERROR;
	}

	char *flag = argv[1];

	if (strcmp(flag, "-q") == 0) {
		if (argc != 6) {
			printf("Error: Invalid number of arguments for -q flag.\n");
			return ARG_ERROR;
		}
		double epsilon = atof(argv[2]);
		double a = atof(argv[3]);
		double b = atof(argv[4]);
		double c = atof(argv[5]);
		solve_quadratic(epsilon, a, b, c);
	} else if (strcmp(flag, "-m") == 0) {
		if (argc != 4) {
			printf("Error: Invalid number of arguments for -m flag.\n");
			return ARG_ERROR;
		}
		int num1 = atoi(argv[2]);
		int num2 = atoi(argv[3]);
		check_multiple(num1, num2);
	} else if (strcmp(flag, "-t") == 0) {
		if (argc != 6) {
			printf("Error: Invalid number of arguments for -t flag.\n");
			return ARG_ERROR;
		}
		double epsilon = atof(argv[2]);
		double side1 = atof(argv[3]);
		double side2 = atof(argv[4]);
		double side3 = atof(argv[5]);
		check_triangle(epsilon, side1, side2, side3);
	} else {
		printf("Error: Unknown flag: %s\n", flag);
		return FLAG_ERROR;
	}

	return SUCCESS;
}
