#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "handlers.h"
#include "error_codes.h"

typedef enum KOpts {
    kOptA,
    kOptB,
    kOptC,
    kOptD
} KOpts;

int GetOpts(int argc, char** argv, KOpts* option, double* precision, double* x) {
    if (argc != 4) {
        printf("Invalid number of arguments\nExpected: 3 arguments\n");
        return E_OUT_OF_RANGE;
    }

    *precision = atof(argv[1]); 
    *x = atof(argv[2]);

    if (strcmp(argv[3], "-a") == 0 || strcmp(argv[3], "/a") == 0) {
        *option = kOptA;
    } else if (strcmp(argv[3], "-b") == 0 || strcmp(argv[3], "/b") == 0) {
        *option = kOptB;
    } else if (strcmp(argv[3], "-c") == 0 || strcmp(argv[3], "/c") == 0) {
        *option = kOptC;
    } else if (strcmp(argv[3], "-d") == 0 || strcmp(argv[3], "/d") == 0) {
        *option = kOptD;
    } else {
        printf("Unknown option: %s\n", argv[3]);
        return E_UNKNOWN_OPT;
    }
    
    return S_OK;
}

int main(int argc, char* argv[]) {
    KOpts opt = kOptA;
    double precision = 0.0;
    double x = 0.0;

    int (*handlers[4])(double, double) = {
        HandlerOpta, HandlerOptb, 
        HandlerOptc, HandlerOptd
    };

    int error_code = GetOpts(argc, argv, &opt, &precision, &x);
    if (error_code != S_OK) {
        printf("Error occurred: %d\n", error_code);
        return error_code;
    }

    error_code = handlers[opt](precision, x);
    if (error_code != S_OK) {
        printf("Handler error: %d\n", error_code);
        return error_code;
    }

    return S_OK;
}
