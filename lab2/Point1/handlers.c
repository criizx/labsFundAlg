#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int HandlerOptL(const char* inputStr) {
	if (!inputStr) {
		return -1;
	}
	return strLen(inputStr);
}

char* HandlerOptR(const char* inputStr) {
	if (!inputStr) return NULL;

	int len = strLen(inputStr);
	char* result = (char*)malloc(len + 1);

	if (!result) return NULL;

	for (int i = 0; i < len; i++) {
		result[i] = inputStr[len - 1 - i];
	}
	result[len] = '\0';

	return result;
}

char* HandlerOptU(const char* inputStr) {
	if (!inputStr) return NULL;

	int len = strLen(inputStr);
	char* result = (char*)malloc(len + 1);

	if (!result) return NULL;

	for (int i = 0; i < len; i++) {
		if (i % 2 == 1) {
			result[i] = toupper(inputStr[i]);
		} else {
			result[i] = inputStr[i];
		}
	}
	result[len] = '\0';

	return result;
}

char* HandlerOptN(const char* inputStr) {
	if (!inputStr) return NULL;

	int len = strLen(inputStr);

	char* digits = (char*)malloc(len + 1);
	char* letters = (char*)malloc(len + 1);
	char* others = (char*)malloc(len + 1);

	if (!digits || !letters || !others) {
		free(digits);
		free(letters);
		free(others);
		return NULL;
	}

	int digitIdx = 0, letterIdx = 0, otherIdx = 0;

	for (int i = 0; inputStr[i] != '\0'; i++) {
		if (isdigit(inputStr[i])) {
			digits[digitIdx++] = inputStr[i];
		} else if (isalpha(inputStr[i])) {
			letters[letterIdx++] = inputStr[i];
		} else {
			others[otherIdx++] = inputStr[i];
		}
	}

	digits[digitIdx] = '\0';
	letters[letterIdx] = '\0';
	others[otherIdx] = '\0';

	char* result = (char*)malloc(digitIdx + letterIdx + otherIdx + 1);
	if (!result) {
		free(digits);
		free(letters);
		free(others);
		return NULL;
	}

	sprintf(result, "%s%s%s", digits, letters, others);

	free(digits);
	free(letters);
	free(others);

	return result;
}

void HandlerOptC(unsigned int seed, int number, char* argv[]) {
	srand(seed);

	int totalLength = 0;
	for (int i = 0; i < number; i++) {
		totalLength += strLen(argv[i]) + 1;
	}

	char* result = (char*)malloc(totalLength);
	if (result == NULL) {
		printf("Ошибка выделения памяти\n");
		return;
	}
	result[0] = '\0';
	shuffleStrings(argv, number);

	for (int i = 0; i < number; i++) {
		strConcat(result, argv[i]);
	}

	printf("Результат: %s\n", result);

	free(result);
}
