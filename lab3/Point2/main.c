#include <stdio.h>

#include "vector.h"

int main() {
	double coords1[] = {1.0, 2.0, 3.0};
	double coords2[] = {-3.0, 4.0, -5.0};

	Vector vectors[] = {{coords1, 3}, {coords2, 3}};

	double p = 3.0;

	findMaxNorm(2, vectors, 3, normInfinity, normP, 2.0, normA);

	return 0;
}
