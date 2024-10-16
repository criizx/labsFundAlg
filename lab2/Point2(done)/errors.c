#include <stdio.h>
#include "errors.h"

void handleError(ErrorCode code) {
    switch (code) {
        case SUCCESS:
            break;
        case ERROR_OVERFLOW:
            printf("Error: Overflow occurred during computation.\n");
            break;
        case ERROR_INVALID_INPUT:
            printf("Error: Invalid input provided.\n");
            break;
        default:
            printf("Error: Unknown error occurred.\n");
    }
}
