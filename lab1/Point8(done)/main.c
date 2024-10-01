#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_BUFFER_SIZE 128

int isDigit(char ch) { return ch >= '0' && ch <= '9'; }

int isAlpha(char ch) { return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'); }

int isAlNum(char ch) { return isAlpha(ch) || isDigit(ch); }

int charToValue(char ch) {
	if (isDigit(ch)) {
		return ch - '0';
	} else if (ch >= 'A' && ch <= 'Z') {
		return ch - 'A' + 10;
	} else if (ch >= 'a' && ch <= 'z') {
		return ch - 'a' + 10;
	}
	return -1;
}

int findMinBase(const char* num) {
	int maxDigit = 1;
	for (int i = 0; num[i] != '\0'; ++i) {
		if (num[i] == ' ') {
			continue;
		}
		int value = charToValue(num[i]);
		if (value == -1) {
			continue;
		}
		if (value + 1 > maxDigit) {
			maxDigit = value + 1;
		}
	}
	if (maxDigit > 36) {
		return 36;
	} else {
		return maxDigit;
	}
}

long long convertToDecimal(const char* num, int base) {
	if (base < 2 || base > 36) {
		fprintf(stderr, "Base must be in the range [2, 36]\n");
		return -1;
	}

	long long result = 0;
	int length = strlen(num);

	for (int i = 0; i < length; ++i) {
		char c = num[i];
		int value;

		if (isDigit(c)) {
			value = c - '0';
		} else if (isAlpha(c)) {
			value = toupper(c) - 'A' + 10;
		} else if (c == ' ') {
			continue;
		} else {
			fprintf(stderr, "Invalid character '%c' for base %d\n", c, base);
			return -1;
		}

		if (value >= base) {
			fprintf(stderr, "Character '%c' out of range for base %d\n", c, base);
			return -1;
		}

		result = result * base + value;
	}

	return result;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Wrong number of arguments\n");
		return 1;
	}

	FILE* inputFile = fopen(argv[1], "r");
	if (!inputFile) {
		printf("Input file could not be opened\n");
		return 1;
	}

	FILE* outputFile = fopen(argv[2], "w");
	if (!outputFile) {
		printf("Output file could not be opened\n");
		fclose(inputFile);
		return 1;
	}

	size_t bufferSize = INITIAL_BUFFER_SIZE;
	char* num = (char*)malloc(bufferSize * sizeof(char));

	if (num == NULL) {
		printf("Memory allocation error\n");
		fclose(inputFile);
		fclose(outputFile);
		return 1;
	}

	int index = 0;
	int ch;

	while ((ch = fgetc(inputFile)) != EOF) {
		if (isAlNum(ch)) {
			num[index++] = ch;
			if (index >= bufferSize) {
				bufferSize *= 2;
				char* temp = (char*)realloc(num, bufferSize * sizeof(char));
				if (temp == NULL) {
					printf("Memory reallocation error\n");
					free(num);
					fclose(inputFile);
					fclose(outputFile);
					return 1;
				}
				num = temp;
			}
		} else if (index > 0) {
			num[index] = '\0';
			index = 0;

			int minBase = findMinBase(num);
			long long decimalValue = convertToDecimal(num, minBase);

			if (decimalValue != -1) {
				fprintf(outputFile, "%s (base %d) = %lld\n", num, minBase, decimalValue);
			}
		}
	}

	if (index > 0) {
		num[index] = '\0';
		int minBase = findMinBase(num);
		long long decimalValue = convertToDecimal(num, minBase);

		if (decimalValue != -1) {
			fprintf(outputFile, "%s (base %d) = %lld\n", num, minBase, decimalValue);
		}
	}

	free(num);
	fclose(inputFile);
	fclose(outputFile);
	return 0;
}
