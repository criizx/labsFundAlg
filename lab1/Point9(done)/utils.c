#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

ErrorCode fillArray(int* array, int size, int min, int max) {
	if (array == NULL) {
		return ERROR_MEMORY_ALLOCATION;
	}
	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		array[i] = min + rand() % (max - min + 1);
	}
	return SUCCESS;
}

void findAndSwapMinMax(int* array, int size) {
	if (array == NULL || size <= 0) return;

	int minIndex = 0, maxIndex = 0;
	for (int i = 1; i < size; i++) {
		if (array[i] < array[minIndex]) {
			minIndex = i;
		}
		if (array[i] > array[maxIndex]) {
			maxIndex = i;
		}
	}

	int temp = array[minIndex];
	array[minIndex] = array[maxIndex];
	array[maxIndex] = temp;
}

int findNearest(int* arrayB, int sizeB, int target) {
	int left = 0, right = sizeB - 1, mid;
	int nearest = arrayB[0];

	while (left <= right) {
		mid = left + (right - left) / 2;

		if (abs(arrayB[mid] - target) < abs(nearest - target)) {
			nearest = arrayB[mid];
		}

		if (arrayB[mid] < target) {
			left = mid + 1;
		} else if (arrayB[mid] > target) {
			right = mid - 1;
		} else {
			return arrayB[mid];
		}
	}

	return nearest;
}

ErrorCode findNearestValue(int* arrayA, int sizeA, int* arrayB, int sizeB, int* arrayC) {
	if (arrayA == NULL || arrayB == NULL || arrayC == NULL) {
		return ERROR_MEMORY_ALLOCATION;
	}

	qsort(arrayB, sizeB, sizeof(int), (int (*)(const void*, const void*))cmpfunc);

	for (int i = 0; i < sizeA; i++) {
		int nearest = findNearest(arrayB, sizeB, arrayA[i]);
		arrayC[i] = arrayA[i] + nearest;
	}

	return SUCCESS;
}

int cmpfunc(const void* a, const void* b) { return (*(int*)a - *(int*)b); }