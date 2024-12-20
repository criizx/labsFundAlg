#ifndef UTILS_H
#define UTILS_H

#include "errors.h"

ErrorCode fillArray(int* array, int size, int min, int max);
void findAndSwapMinMax(int* array, int size);
ErrorCode findNearestValue(int* arrayA, int sizeA, int* arrayB, int sizeB, int* arrayC);
int findNearest(int* arrayB, int sizeB, int target);
int cmpfunc(const void* a, const void* b);

#endif
