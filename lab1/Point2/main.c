#include <stdio.h>
#include "functions.h"
#include "error_codes.h"
#include "polynomials.h"

typedef enum {
	METHOD_LIMIT,
	METHOD_SERIES,
	METHOD_EQUATION
} MethodType;

typedef enum {
	CONSTANT_E,
	CONSTANT_PI,
	CONSTANT_LN2,
	CONSTANT_SQRT2,
	CONSTANT_EULER_MASCHERONI
} ConstantType;

int main() {
	MethodType method;
	ConstantType constant;
	double precision, low, high;

	printf("Select constant to calculate:\n");
	printf("1 - e\n");
	printf("2 - pi\n");
	printf("3 - ln(2)\n");
	printf("4 - sqrt(2)\n");
	printf("5 - Euler-Mascheroni constant\n");
	int constant_input;
	scanf("%d", &constant_input);

	switch (constant_input) {
		case 1: constant = CONSTANT_E; break;
		case 2: constant = CONSTANT_PI; break;
		case 3: constant = CONSTANT_LN2; break;
		case 4: constant = CONSTANT_SQRT2; break;
		case 5: constant = CONSTANT_EULER_MASCHERONI; break;
		default: printf("Invalid constant selected\n"); return E_INPUT_ERROR;
	}

	printf("Select method to calculate:\n");
	printf("1 - Limit\n");
	printf("2 - Series/Product\n");
	printf("3 - Equation\n");
	int method_input;
	scanf("%d", &method_input);

	switch (method_input) {
		case 1: method = METHOD_LIMIT; break;
		case 2: method = METHOD_SERIES; break;
		case 3: method = METHOD_EQUATION; break;
		default: printf("Invalid method selected\n"); return E_INPUT_ERROR;
	}

	printf("Enter precision for calculation (e.g., 0.0001): ");
	scanf("%lf", &precision);

	switch (method) {
		case METHOD_LIMIT:
			switch (constant) {
				case CONSTANT_E:
					printf("e (limit) = %lf\n", CalculateELimit(precision));
					break;
				case CONSTANT_PI:
					printf("pi (limit) = %lf\n", CalculatePiLimit(precision));
					break;
				case CONSTANT_LN2:
					printf("ln(2) (limit) = %lf\n", CalculateLn2Limit(precision));
					break;
				case CONSTANT_SQRT2:
					printf("sqrt(2) (limit) = %lf\n", CalculateSqr2Limit(precision));
					break;
				case CONSTANT_EULER_MASCHERONI:
					printf("Euler-Mascheroni constant (limit) = %lf\n", CalculateYLimit(precision));
					break;
				default: printf("Invalid constant selected\n"); return E_INPUT_ERROR;
			}
			break;

		case METHOD_SERIES:
			switch (constant) {
				case CONSTANT_E:
					printf("e (series) = %lf\n", CalculateESeries(precision));
					break;
				case CONSTANT_PI:
					printf("pi (series) = %lf\n", CalculatePiSeries(precision));
					break;
				case CONSTANT_LN2:
					printf("ln(2) (series) = %lf\n", CalculateLn2Series(precision));
					break;
				case CONSTANT_SQRT2:
					printf("sqrt(2) (series) = %lf\n", CalculateSqr2Series(precision));
					break;
				case CONSTANT_EULER_MASCHERONI:
					printf("Euler-Mascheroni constant (series) = %lf\n", CalculateYSeries(precision));
					break;
				default: printf("Invalid constant selected\n"); return E_INPUT_ERROR;
			}
			break;

		case METHOD_EQUATION:
			switch (constant) {
				case CONSTANT_E:
					printf("Enter lower bound: ");
					scanf("%lf", &low);
					printf("Enter upper bound: ");
					scanf("%lf", &high);
					printf("e (equation) = %lf\n", CalculateRootUsingEquation(CalculateELimit, low, high, precision));
					break;
				case CONSTANT_PI:
					printf("Enter lower bound: ");
					scanf("%lf", &low);
					printf("Enter upper bound: ");
					scanf("%lf", &high);
					printf("pi (equation) = %lf\n", CalculateRootUsingEquation(CalculatePiLimit, low, high, precision));
					break;
				case CONSTANT_LN2:
					printf("Enter lower bound: ");
					scanf("%lf", &low);
					printf("Enter upper bound: ");
					scanf("%lf", &high);
					printf("ln(2) (equation) = %lf\n", CalculateRootUsingEquation(CalculateLn2Limit, low, high, precision));
					break;
				case CONSTANT_SQRT2:
					printf("Enter lower bound: ");
					scanf("%lf", &low);
					printf("Enter upper bound: ");
					scanf("%lf", &high);
					printf("sqrt(2) (equation) = %lf\n", CalculateRootUsingEquation(CalculateSqr2Limit, low, high, precision));
					break;
				case CONSTANT_EULER_MASCHERONI:
					printf("Enter lower bound: ");
					scanf("%lf", &low);
					printf("Enter upper bound: ");
					scanf("%lf", &high);
					printf("Euler-Mascheroni constant (equation) = %lf\n", CalculateRootUsingEquation(CalculateYLimit, low, high, precision));
					break;
				default: printf("Invalid constant selected\n"); return E_INPUT_ERROR;
			}
			break;

		default: printf("Invalid method selected\n"); return E_INPUT_ERROR;
	}

	return S_OK;
}
