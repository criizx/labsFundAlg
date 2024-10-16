#ifndef ERRORS_H
#define ERRORS_H

typedef enum {
    SUCCESS = 0,
    ERROR_OVERFLOW = -1,
    ERROR_INVALID_INPUT = -2
} ErrorCode;

void handleError(ErrorCode code);

#endif