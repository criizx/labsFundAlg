#include "handlers.h"

#include <stdio.h>

#include "errors.h"
#include "functions.h"

int HandleOptQ(double* args) {
	double epsilon = args[0];
	double a = args[1];
	double b = args[2];
	double c = args[3];

	double permutations[6][3] = {{a, b, c}, {a, c, b}, {b, a, c}, {b, c, a}, {c, a, b}, {c, b, a}};

	for (int i = 0; i < 6; i++) {
		printf("Solving for coefficients: a = %lf, b = %lf, c = %lf\n", permutations[i][0], permutations[i][1],
		       permutations[i][2]);

		double root1 = 0.0, root2 = 0.0;

		int num_roots =
		    solve_quadratic(epsilon, permutations[i][0], permutations[i][1], permutations[i][2], &root1, &root2);

		print_quadratic_result(num_roots, root1, root2);
		printf("\n");
	}

	return SUCCESS;
}

int HandleOptM(double* args) {
	int num1 = (int)args[0];
	int num2 = (int)args[1];

	if (check_multiple(num1, num2)) {
		printf("%d is not a multiple of %d.\n", num1, num2);
	} else {
		printf("%d is a multiple of %d.\n", num1, num2);
	}

	return SUCCESS;
}

int HandleOptT(double* args) {
	double epsilon = args[0];
	double side1 = args[1];
	double side2 = args[2];
	double side3 = args[3];

	if (check_triangle(epsilon, side1, side2, side3)) {
		printf("The numbers form a right triangle.\n");
	} else {
		printf("The numbers do not form a right triangle.\n");
	}
	
	return SUCCESS;
}
