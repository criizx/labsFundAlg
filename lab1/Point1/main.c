#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "handlers.h"
#include "error_codes.h"

typedef enum kOpts {
    OPT_H,
    OPT_P,
    OPT_S,
    OPT_E,
    OPT_A,
    OPT_F
} kOpts;

int GetOpts(int argc, char** argv, kOpts *option, int *number){
    if (argc != 3) {
        printf("Invalid number of arguments\nExpected: 2 arguments\n");
        return E_OUT_OF_RANGE;
    }

    *number = atoi(argv[1]);

    if (strcmp(argv[2], "-h") == 0) {
        *option = OPT_H;
    } else if (strcmp(argv[2], "-p") == 0) {
        *option = OPT_P;
    } else if (strcmp(argv[2], "-s") == 0) {
        *option = OPT_S;
    } else if (strcmp(argv[2], "-e") == 0) {
        *option = OPT_E;
    } else if (strcmp(argv[2], "-a") == 0) {
        *option = OPT_A;
    } else if (strcmp(argv[2], "-f") == 0) {
        *option = OPT_F;
    } else {
        printf("Unknown option: %s\n", argv[2]);
        return E_UNKNOWN_OPT;
    }

    return S_OK;
};


int main(int argc, char* argv[]) {
    kOpts opt = 0;
    int procceedNumber = 0;

    void (*handlers[6])(int) = {
        HandlerOptH,
        HandlerOptP,
        HandlerOptS,
        HandlerOptE,
        HandlerOptA,
        HandlerOptF
    };

    if (GetOpts(argc, argv, &opt, &procceedNumber) != 0){
        return 1;
    }

    handlers[opt](procceedNumber);

    return S_OK;
}
