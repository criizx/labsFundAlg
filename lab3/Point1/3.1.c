#include <stdio.h>
#include <stdlib.h>

unsigned int bitwiseAdd(int a, int b) {
    if (b < 0) {
        b = bitwiseAdd(~(-b), 1);
    }
    while (b != 0) {
        unsigned int carry = a & b;
        a = a ^ b;
        b = carry << 1;
    }
    return a;
}

void convertToBase2R(unsigned int num, int r) {
    unsigned int base = 1 << r;
    unsigned int mask = bitwiseAdd(base, bitwiseAdd(~1, 1));

    char* result = (char*) malloc(32 * sizeof(char));
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
    for (int j = bitwiseAdd(i, bitwiseAdd(~1, 1)); j >= 0; j = bitwiseAdd(j, bitwiseAdd(~1, 1))) {
        if (r == 1 || r == 2 || r == 4) {
            printf("%X", result[j]);
        } 
        else if (r == 3) {
            printf("%o", result[j]);
        } 
        else if (r == 5) {
            if (result[j] < 10) {
                printf("%d", result[j]);
            } else {
                printf("%c", bitwiseAdd('A', bitwiseAdd(result[j], bitwiseAdd(~10, 1))));
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
    if (input < 0) {
        printf("Error: number must be non-negative\n");
        return 1;
    }
    *num = (unsigned int)input;

    printf("Enter r (base power of 2^r): ");
    if (scanf("%d", r) != 1 || *r < 1 || *r > 5) {
        printf("Error: r must be an integer between 1 and 5\n");
        return 1;
    }
    
    return 0;
}

int main() {
    unsigned int num;
    int r;

    if (validateInput((int*)&num, &r)) {
        return 1;
    }
    convertToBase2R(num, r);
    return 0;
}
