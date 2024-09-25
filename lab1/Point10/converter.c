#include "converter.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

void convertToBase(int num, int base, char *result) {
	const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	char buffer[50];
	int isNegative = num < 0;
	num = abs(num);
	int i = 0;

	if (num == 0) {
		strcpy(result, "0");
		return;
	}

	while (num > 0) {
		buffer[i++] = digits[num % base];
		num /= base;
	}

	if (isNegative) {
		buffer[i++] = '-';
	}

	buffer[i] = '\0';

	int len = strlen(buffer);
	for (int j = 0; j < len; j++) {
		result[j] = buffer[len - j - 1];
	}
	result[len] = '\0';
}