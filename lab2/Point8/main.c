#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1000

int charToValue(char c) {
	if (isdigit(c)) return c - '0';
	return toupper(c) - 'A' + 10;
}

char valueToChar(int val) {
	if (val < 10) return val + '0';
	return val - 10 + 'A';
}

int addInColumn(char* num1, char* num2, int base, char* result) {
	int len1 = strlen(num1);
	int len2 = strlen(num2);
	int maxLen = len1 > len2 ? len1 : len2;
	int carry = 0, i, sum;

	result[maxLen + 1] = '\0';
	for (i = 0; i < maxLen || carry; i++) {
		int digit1 = i < len1 ? charToValue(num1[len1 - 1 - i]) : 0;
		int digit2 = i < len2 ? charToValue(num2[len2 - 1 - i]) : 0;

		if (digit1 >= base || digit2 >= base) {
			printf("Error: Invalid digit for base %d\n", base);
			return 0;
		}

		sum = digit1 + digit2 + carry;
		carry = sum / base;
		result[maxLen - i - 1] = valueToChar(sum % base);
	}

	int firstNonZero = 0;
	while (result[firstNonZero] == '0' && result[firstNonZero + 1] != '\0') {
		firstNonZero++;
	}

	if (firstNonZero > 0) {
		strcpy(result, result + firstNonZero);
	}

	return 1;
}

void sumNumbers(int base, int count, ...) {
	if (base < 2 || base > 36) {
		printf("Error: Invalid base %d. Base should be between 2 and 36.\n", base);
		return;
	}

	char result[MAX_LEN] = "0";
	char temp[MAX_LEN];

	va_list args;
	va_start(args, count);

	for (int i = 0; i < count; i++) {
		char* number = va_arg(args, char*);
		strcpy(temp, result);
		if (!addInColumn(temp, number, base, result)) {
			printf("Aborting the sum due to an error.\n");
			va_end(args);
			return;
		}
	}

	va_end(args);

	printf("Result: %s\n", result);
}

int main() {
	sumNumbers(2, 3, "0000", "0000101", "010");
	return 0;
}
