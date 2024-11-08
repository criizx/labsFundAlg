#include "vector.h"

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

double normInfinity(Vector v) {
	double maxVal = fabs(v.coordinates[0]);
	for (int i = 1; i < v.dimension; i++) {
		if (fabs(v.coordinates[i]) > maxVal) {
			maxVal = fabs(v.coordinates[i]);
		}
	}
	return maxVal;
}

double normP(Vector v, double p) {
	double sum = 0.0;
	for (int i = 0; i < v.dimension; i++) {
		sum += pow(fabs(v.coordinates[i]), p);
	}
	return pow(sum, 1.0 / p);
}

double normA(Vector v) {
	double **A = (double **)malloc(v.dimension * sizeof(double *));
	for (int i = 0; i < v.dimension; i++) {
		A[i] = (double *)malloc(v.dimension * sizeof(double));
		for (int j = 0; j < v.dimension; j++) {
			A[i][j] = (i == j) ? 1.0 : 0.0;
		}
	}

	double sum = 0.0;
	for (int i = 0; i < v.dimension; i++) {
		for (int j = 0; j < v.dimension; j++) {
			sum += v.coordinates[i] * A[i][j] * v.coordinates[j];
		}
	}

	for (int i = 0; i < v.dimension; i++) {
		free(A[i]);
	}
	free(A);

	return sqrt(sum);
}

void findMaxNorm(int numVectors, Vector *vectors, int numNorms, ...) {
	va_list norms;
	va_start(norms, numNorms);

	for (int n = 0; n < numNorms; n++) {
		double (*normFunc)(Vector, ...);
		normFunc = va_arg(norms, double (*)(Vector, ...));

		double p = 0.0;
		if (normFunc == (double (*)(Vector, ...))normP) {
			p = va_arg(norms, double);
		}

		double maxNorm = (p > 0) ? normFunc(vectors[0], p) : normFunc(vectors[0]);
		Vector maxVector = vectors[0];

		for (int i = 1; i < numVectors; i++) {
			double currentNorm = (p > 0) ? normFunc(vectors[i], p) : normFunc(vectors[i]);
			if (currentNorm > maxNorm) {
				maxNorm = currentNorm;
				maxVector = vectors[i];
			}
		}

		printf("Max norm value: %f\n", maxNorm);
		printf("Max vector: [");
		for (int i = 0; i < maxVector.dimension; i++) {
			printf("%f ", maxVector.coordinates[i]);
		}
		printf("]\n");
	}

	va_end(norms);
}
