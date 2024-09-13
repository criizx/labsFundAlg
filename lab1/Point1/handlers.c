#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "handlers.h"
#include "functions.h"
#include "error_codes.h"

int HandlerOptH(int inputNum){
    if (inputNum <= 0 || inputNum > 100) {
        printf("There is not a single natural number that is a multiple of %d in the range from 1 to 100\n", inputNum);
        return E_OUT_OF_RANGE;
    }
    for (int i = 1; i <= 100; ++i) {
        if (i % inputNum == 0) {
            printf("%d\n", i);
        }
    }
    return S_OK;
}

int HandlerOptP(int inputNum) {
    if (inputNum < 0){
        printf("Number must be positive for prime check\n");
        return E_OUT_OF_RANGE;
    }
    if (isPrime(inputNum)) {
        printf("%d is prime number\n", inputNum);
    } else {
        printf("%d is composite number\n", inputNum);
    }
    return S_OK;
}

int HandlerOptS(int inputNum){
    decToHex(inputNum);
    return S_OK;
}

int HandlerOptE(int inputNum){
    if (inputNum >= 10) {
        printf("Input number is bigger than 10\n");
        return E_OUT_OF_RANGE;
    }
    printf("base | ");
    for (int i = 1; i <= inputNum; i++) {
        printf("degree %d | ", i);
    }
    printf("\n");
    for (int base = 1; base <= 10; base++) {
        printf("%9d | ", base);
        for (int exp = 1; exp <= inputNum; exp++) {
            printf("%9.0f | ", pow(base, exp));
        }
        printf("\n");
    }    
    return S_OK;
}

int HandlerOptA(int inputNum){
    printf("%d", sumFactorial(inputNum));
    return S_OK;
}

int HandlerOptF(int inputNum){
    printf("%llu\n", factorial(inputNum));
    return S_OK;
}