#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "handlers.h"

typedef enum kOpts {
    OPT_H,
    OPT_P,
    OPT_S,
    OPT_E,
    OPT_A,
    OPT_F
} kOpts;

int GetOpts(int argc, char** argv, kOpts *option, int *number);


int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Invalid number of arguments\nExpected: 2 arguments\n");
        return 1;
    }

    int inputNum = atoi(argv[1]);
    int result = 0;

    if (strcmp(argv[2], "-h") == 0) {
        result = HandlerOptH(inputNum);
    } else if (strcmp(argv[2], "-p") == 0) {
        result = HandlerOptP(inputNum);
    } else if (strcmp(argv[2], "-s") == 0) {
        result = HandlerOptS(inputNum);
    } else if (strcmp(argv[2], "-e") == 0) {
        result = HandlerOptE(inputNum);
    } else if (strcmp(argv[2], "-a") == 0) {
        result = HandlerOptA(inputNum);
    } else if (strcmp(argv[2], "-f") == 0) {
        result = HandlerOptF(inputNum);
    } else {
        printf("Unknown option: %s\n", argv[2]);
        return 1;
    }

    if (result != 0) {
        printf("An error occurred while processing option %s with input %d\n", argv[2], inputNum);
        return 1;
    }

    return 0;
}
