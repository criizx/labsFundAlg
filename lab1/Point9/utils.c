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

ErrorCode findNearestValue(int* arrayA, int sizeA, int* arrayB, int sizeB, int* arrayC) {
	if (arrayA == NULL || arrayB == NULL || arrayC == NULL) return ERROR_MEMORY_ALLOCATION;

	for (int i = 0; i < sizeA; i++) {
		int nearest = arrayB[0];
		int minDiff = abs(arrayA[i] - arrayB[0]);

		for (int j = 1; j < sizeB; j++) {
			int diff = abs(arrayA[i] - arrayB[j]);
			if (diff < minDiff) {
				nearest = arrayB[j];
				minDiff = diff;
			}
		}

		arrayC[i] = arrayA[i] + nearest;
	}

	return SUCCESS;
}
