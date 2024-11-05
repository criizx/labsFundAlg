#include <math.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int bitwiseAdd(int a, int b) {
	while (b != 0) {
		unsigned int carry = a & b;
		a = a ^ b;
		b = carry << 1;
	}
	return a;
}

unsigned int bitwiseNegate(int a) { return bitwiseAdd(~a, 1); }

void convertToBase2R(unsigned int num, int r, int flag) {
	unsigned int base = 1 << r;
	unsigned int mask = bitwiseAdd(base, bitwiseNegate(1));

	char* result = (char*)malloc(32 * sizeof(char));
	if (result == NULL) {
		printf("Error: insufficient memory\n");
		exit(1);
	}

	int i = 0;
	while (num) {
		result[i] = (num & mask);
		num >>= r;
		i = bitwiseAdd(i, 1);
	}

	printf("Number in base 2^%d: ", r);
	if (flag) {
		printf("-");
	}
	for (int j = bitwiseAdd(i, bitwiseNegate(1)); j >= 0; j = bitwiseAdd(j, bitwiseNegate(1))) {
		if (r == 1 || r == 2 || r == 4) {
			printf("%X", result[j]);
		} else if (r == 3) {
			printf("%o", result[j]);
		} else if (r == 5) {
			if (result[j] < 10) {
				printf("%d", result[j]);
			} else {
				printf("%c", bitwiseAdd('A', bitwiseAdd(result[j], bitwiseNegate(10))));
			}
		}
	}
	printf("\n");

	free(result);
}

int validateInput(int* num, int* r) {
	int input;
	printf("Enter a number: ");
	if (scanf("%d", &input) != 1) {
		printf("Error: invalid input for number\n");
		return 1;
	}
	*num = (int)input;

	printf("Enter r (base power of 2^r): ");
	if (scanf("%d", r) != 1 || *r < 1 || *r > 5) {
		printf("Error: r must be an integer between 1 and 5\n");
		return 1;
	}

	return 0;
}

int main() {
	int num;
	int r;
	int Flag = 0;

	if (validateInput((int*)&num, &r)) {
		return 1;
	}

	if (num < 0) {
		Flag = 1;
		num = bitwiseNegate(num);
	}
	convertToBase2R(num, r, Flag);
	return 0;
}
