#include <stdio.h>
#include <stdlib.h>

#include "error_codes.h"
#include "handlers.h"
#include "utils.h"

typedef enum KOpts { kOptL, kOptR, kOptU, kOptN, kOptC } KOpts;

int getOpts(int argc, char** argv, KOpts* option, unsigned int* number) {
    if (myStrcmp(argv[1], "-c") == 0) {
        if (argc < 4) {
            printf(
                "Invalid number of arguments for -c flag\nExpected: at least 3 arguments (flag, number, and one or more strings)\n");
            return E_OUT_OF_RANGE;
        }
        *option = kOptC;

        char* endptr;
        *number = strtoul(argv[2], &endptr, 10);
        if (*endptr != '\0') {
            printf("Invalid input format: %s is not a valid number\n", argv[2]);
            return E_INVALID_FORMAT;
        }
    } else {
        if (argc != 3) {
            printf("Invalid number of arguments for %s flag\nExpected: 2 arguments (flag and string)\n", argv[1]);
            return E_OUT_OF_RANGE;
        }

        if (myStrcmp(argv[1], "-l") == 0) {
            *option = kOptL;
        } else if (myStrcmp(argv[1], "-r") == 0) {
            *option = kOptR;
        } else if (myStrcmp(argv[1], "-u") == 0) {
            *option = kOptU;
        } else if (myStrcmp(argv[1], "-n") == 0) {
            *option = kOptN;
        } else {
            printf("Unknown option: %s\n", argv[1]);
            return E_UNKNOWN_OPT;
        }
    }

    return S_OK;
}

int main(int argc, char* argv[]) {
    KOpts opt;
    unsigned int number = 0;

    int errorCode = getOpts(argc, argv, &opt, &number);
    if (errorCode != S_OK) {
        printf("Error occurred: %d\n", errorCode);
        return errorCode;
    }

    int (*handlersWithString[4])(const char*) = {HandlerOptL, HandlerOptR, HandlerOptU, HandlerOptN};

    if (opt == kOptC) {
        errorCode = HandlerOptC(number,argc - 3, &argv[3]);
    } else {
        errorCode = handlersWithString[opt](argv[2]);
    }

    if (errorCode != S_OK) {
        printf("Handler error: %d\n", errorCode);
        return errorCode;
    }

    return S_OK;
}
