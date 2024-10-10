#include <stdio.h>
#include <string.h>

int HandlerOptL(const char* inputStr) {
	printf("Length of the string: %lu\n", strLen(inputStr));
	return 0;
}

int HandlerOptR(const char* inputStr) {
	int len = strLen(inputStr);
	for (int i = len - 1; i >= 0; i--) {
		putchar(inputStr[i]);
	}
	putchar('\n');
	return 0;
}

int HandlerOptU(const char* inputStr) {
	for (int i = 0; inputStr[i] != '\0'; i++) {
		if (i % 2 == 0) {
			putchar(inputStr[i]);
		} else {
			putchar(toupper(inputStr[i]));
		}
	}
	putchar('\n');
	return 0;
}

int HandlerOptN(const char* inputStr) {
	char digits[100], letters[100];
	int digitIdx = 0, letterIdx = 0;

	for (int i = 0; inputStr[i] != '\0'; i++) {
		if (isdigit(inputStr[i])) {
			digits[digitIdx++] = inputStr[i];
		} else if (isalpha(inputStr[i])) {
			letters[letterIdx++] = inputStr[i];
		}
	}
	digits[digitIdx] = '\0';
	letters[letterIdx] = '\0';

	printf("Result: %s%s\n", digits, letters);
	return 0;
}

int HandlerOptC(unsigned int seed, int argc, char* argv[]) { srand(seed); }
