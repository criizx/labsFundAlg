#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    double *coordinates;
    int dimension;
} Vector;

double normInfinity(Vector v);
double normP(Vector v, double p);
double normA(Vector v);
void findMaxNorm(int numVectors, Vector *vectors, int numNorms, ...);

#endif
