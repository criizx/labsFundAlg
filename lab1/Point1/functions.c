#include <stdio.h>
#include <math.h>
#include "error_codes.h"
#include "functions.h"

#define HEX_SIZE 100

void decToHex(int n) {
    if (n < 0){
        printf("Number must be non-negative for hex conversation");
        return E_INVALID_ARG;
    }

    char hex[HEX_SIZE];
    int i = 0;

    if (n == 0) {
        printf("0");
        return S_OK;
    }

    while (n != 0) {
        int remainder = n % 16;
        if (remainder < 10) {
            hex[i] = remainder + '0';
        } else {
            hex[i] = remainder - 10 + 'A';
        }
        n = n / 16;
        i++;
    }
    for (int j = i - 1; j >= 0; j--) {
        printf("%c ", hex[j]);
    }
    return S_OK;
}

int sumFactorial(int n) {
    int result = 0;
    for (int i = 1; i <= n; ++i) {
        result += i;
    }
    return result;
}

unsigned long long factorial(int n) {
    if (n < 0){
        printf("There is no factorial for negative nums\n");
        return E_INVALID_ARG;
    }
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

int isPrime(int numForCheck) {
    if (numForCheck < 2) {
        return 1;
    }
    int maxVal = sqrt(numForCheck);
    for (int i = 2; i <= maxVal; ++i) {
        if (numForCheck % i == 0) {
            return 0;
        }
    }
}
