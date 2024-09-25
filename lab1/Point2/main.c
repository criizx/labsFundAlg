#include <stdio.h>

#include "error_codes.h"
#include "functions.h"
#include "polynomials.h"

int main() {
	double precision;
	double low = 0.0, high = 1000.0;

	printf("Enter precision (e.g., 0.00001): ");
	scanf("%lf", &precision);
	if (precision < 0.00001) {
		printf("Precision is too big");
		return E_INPUT_ERROR;
	}

	printf("Calculating e:\n");
	printf("Limit Method: %.15f\n", CalculateELimit(precision));
	printf("Series Method: %.15f\n", CalculateESeries(precision));
	printf("Equation Method: %.15f\n", CalculateRootUsingEquation(polinomE, low, high, precision));

	printf("\nCalculating pi:\n");
	printf("Limit Method: %.15f\n", CalculatePiLimit(precision));
	printf("Series Method: %.15f\n", CalculatePiSeries(precision));
	printf("Equation Method: %.15f\n", CalculateRootUsingEquation(polinomPi, low, 4, precision));

	printf("\nCalculating ln(2):\n");
	printf("Limit Method: %.15f\n", CalculateLn2Limit(precision));
	printf("Series Method: %.15f\n", CalculateLn2Series(precision));
	printf("Equation Method: %.15f\n", CalculateRootUsingEquation(polinomLn2, low, high, precision));

	printf("\nCalculating sqrt(2):\n");
	printf("Limit Method: %.15f\n", CalculateSqr2Limit(precision));
	printf("Series Method: %.15f\n", CalculateSqr2Series(precision));
	printf("Equation Method: %.15f\n", CalculateRootUsingEquation(polinomSqrt2, low, high, precision));

	printf("\nCalculating Euler-Mascheroni constant:\n");
	printf("Limit Method: %.15f\n", CalculateYLimit(precision));
	printf("Series Method: %.15f\n", CalculateYSeries(precision));
	printf("Equation Method: %.15f\n", CalculateRootUsingEquation(polinomEulerMascheroni, low, high, precision));

	return S_OK;
}
