#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "handlers.h"
#include "functions.h"

int HandlerOptH(int inputNum){
    if (inputNum <= 0 || inputNum > 100) {
        printf("There is not a single natural number that is a multiple of %d in the range from 1 to 100\n", inputNum);
        return 1;
    }
    for (int i = 1; i < 101; ++i) {
        if (i % inputNum == 0) {
            printf("%d\n", i);
        }
    }
    return 0;
}

int HandlerOptP(int inputNum) {
    if (isSimple(inputNum)) {
        printf("%d is prime number\n", inputNum);
    } else {
        printf("%d is composite number\n", inputNum);
    }
    return 0;
}

int HandlerOptS(int inputNum){
    decToHex(inputNum);
    return 0;
}

int HandlerOptE(int inputNum){
    if (inputNum < 10) {
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
    } else {
        printf("Input number is bigger than 10\n");
        return 1;
    }
    return 0;
}

int HandlerOptA(int inputNum){
    printf("%d", sumFactorial(inputNum));
    return 0;
}

int HandlerOptF(int inputNum){
    printf("%llu\n", factorial(inputNum));
    return 0;
}