#ifndef ERROR_CODES_H
#define ERROR_CODES_H

typedef enum{
    S_OK = 0,
    E_INVALID_ARG = 1,
    E_BAD_ALLOC = 2,
    E_OUT_OF_RANGE = 3,
    E_UNKNOWN_OPT = 4
} ErrorCode;

#endif