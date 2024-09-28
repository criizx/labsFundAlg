#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main(int argc, char* argv[]) {
	if (argc != 4) {
		printf("Usage: %s <size> <min> <max>\n", argv[0]);
		return ERROR_INVALID_ARGUMENTS;
	}

	// 1
	int sizeA1 = atoi(argv[1]);
	int min = atoi(argv[2]);
	int max = atoi(argv[3]);

	int* arrayA1 = (int*)malloc(sizeA1 * sizeof(int));
	if (arrayA1 == NULL) {
		printf("Memory allocation failed for array A\n");
		return ERROR_MEMORY_ALLOCATION;
	}

	if (fillArray(arrayA1, sizeA1, min, max) != SUCCESS) {
		printf("Error while filling array A\n");
		free(arrayA1);
		return ERROR_MEMORY_ALLOCATION;
	}
	printf("First Array A (before swapping min and max):\n");
	for (int i = 0; i < sizeA1; i++) {
		printf("%d ", arrayA1[i]);
	}
	printf("\n\n");

	findAndSwapMinMax(arrayA1, sizeA1);

	printf("First Array A (after swapping min and max):\n");
	for (int i = 0; i < sizeA1; i++) {
		printf("%d ", arrayA1[i]);
	}
	printf("\n\n");

	free(arrayA1);

	// 2
	int sizeA2 = rand() % 9991 + 10;
	int sizeB = rand() % 9991 + 10;

	int* arrayA2 = (int*)malloc(sizeA2 * sizeof(int));
	if (arrayA2 == NULL) {
		printf("Memory allocation failed for array A\n");
		return ERROR_MEMORY_ALLOCATION;
	}

	int* arrayB = (int*)malloc(sizeB * sizeof(int));
	if (arrayB == NULL) {
		printf("Memory allocation failed for array B\n");
		free(arrayA2);
		return ERROR_MEMORY_ALLOCATION;
	}

	if (fillArray(arrayA2, sizeA2, 10, 10000) != SUCCESS) {
		printf("Error while filling array A\n");
		free(arrayA2);
		free(arrayB);
		return ERROR_MEMORY_ALLOCATION;
	}

	if (fillArray(arrayB, sizeB, -1000, 1000) != SUCCESS) {
		printf("Error while filling array B\n");
		free(arrayA2);
		free(arrayB);
		return ERROR_MEMORY_ALLOCATION;
	}

	int* arrayC = (int*)malloc(sizeA2 * sizeof(int));
	if (arrayC == NULL) {
		printf("Memory allocation failed for array C\n");
		free(arrayA2);
		free(arrayB);
		return ERROR_MEMORY_ALLOCATION;
	}

	if (findNearestValue(arrayA2, sizeA2, arrayB, sizeB, arrayC) != SUCCESS) {
		printf("Error while forming array C\n");
		free(arrayA2);
		free(arrayB);
		free(arrayC);
		return ERROR_MEMORY_ALLOCATION;
	}

	printf("Second Array A:\n");
	for (int i = 0; i < sizeA2; i++) {
		printf("%d ", arrayA2[i]);
	}
	printf("\n");

	printf("Array B:\n");
	for (int i = 0; i < sizeB; i++) {
		printf("%d ", arrayB[i]);
	}
	printf("\n");

	printf("Array C (A[i] + nearest value from B):\n");
	for (int i = 0; i < sizeA2; i++) {
		printf("%d ", arrayC[i]);
	}
	printf("\n");

	free(arrayA2);
	free(arrayB);
	free(arrayC);

	return SUCCESS;
}
