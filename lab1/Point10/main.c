#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "converter.h"
#include "errors.h"

void printError(ErrorCode code);

int main() {
	int base;
	printf("Enter the base of the number system (from 2 to 36): ");
	scanf("%d", &base);

	if (base < 2 || base > 36) {
		printf("ERR_INVALID_BASE");
		return ERR_INVALID_BASE;
	}

	char input[50];
	int maxNumber = 0;
	int firstNumber = 1;
	int isNegative = 0;
	ErrorCode error = ERR_OK;

	int *numbers = NULL;
	int count = 0;
	int capacity = 0;

	printf("You selected base %d. Now enter numbers in base %d (type 'Stop' to finish):\n", base, base);

	while (1) {
		scanf("%s", input);

		if (strcmp(input, "Stop") == 0) break;

		char *endptr;
		int number = strtol(input, &endptr, base);

		if (*endptr != '\0') {
			printError(ERR_INVALID_NUMBER);
			error = ERR_INVALID_NUMBER;
			continue;
		}

		if (count == capacity) {
			if (capacity == 0) {
				capacity = 10;
			} else {
				capacity *= 2;
			}
			numbers = realloc(numbers, capacity * sizeof(int));
			if (numbers == NULL) {
				printf("Memory allocation error!\n");
				return 1;
			}
		}

		numbers[count++] = number;

		if (firstNumber) {
			maxNumber = number;
			isNegative = (number < 0);
			firstNumber = 0;
		} else {
			if (abs(number) > abs(maxNumber)) {
				maxNumber = number;
				isNegative = (number < 0);
			}
		}
	}

	if (firstNumber) {
		printError(ERR_NO_NUMBERS_ENTERED);
		free(numbers);
		return ERR_NO_NUMBERS_ENTERED;
	}

	if (isNegative) {
		printf("Maximum absolute number (in decimal): %d\n", -abs(maxNumber));
	} else {
		printf("Maximum absolute number (in decimal): %d\n", abs(maxNumber));
	}

	int bases[] = {9, 18, 27, 36};
	int numToConvert = 0;
	if (isNegative) {
		numToConvert = -abs(maxNumber);
	} else {
		numToConvert = abs(maxNumber);
	}
	for (int i = 0; i < 4; i++) {
		char converted[50];
		convertToBase(numToConvert, bases[i], converted);
		printf("Representation in base %d: %s\n", bases[i], converted);
	}

	free(numbers);

	return ERR_OK;
}

void printError(ErrorCode code) {
	switch (code) {
		case ERR_INVALID_BASE:
			printf("Error: base must be between 2 and 36.\n");
			break;
		case ERR_INVALID_NUMBER:
			printf("Error: invalid number entered.\n");
			break;
		case ERR_NO_NUMBERS_ENTERED:
			printf("Error: no numbers were entered.\n");
			break;
		case ERR_OK:
		default:
			break;
	}
}