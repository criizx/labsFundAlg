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

    printf("Enter precision (e.g., 0.00001): ");
    scanf("%lf", &precision);

    printf("Enter lower bound for equation method: ");
    scanf("%lf", &low);

    printf("Enter upper bound for equation method: ");
    scanf("%lf", &high);

    double result = 0.0;

    switch (constant) {
        case CONSTANT_E:
            if (method == METHOD_LIMIT) result = CalculateELimit(precision);
            else if (method == METHOD_SERIES) result = CalculateESeries(precision);
            else result = CalculateRootUsingEquation(polinomE, low, high, precision);
            break;
        case CONSTANT_PI:
            if (method == METHOD_LIMIT) result = CalculatePiLimit(precision);
            else if (method == METHOD_SERIES) result = CalculatePiSeries(precision);
            else result = CalculateRootUsingEquation(polinomPi, low, high, precision);
            break;
        case CONSTANT_LN2:
            if (method == METHOD_LIMIT) result = CalculateLn2Limit(precision);
            else if (method == METHOD_SERIES) result = CalculateLn2Series(precision);
            else result = CalculateRootUsingEquation(polinomLn2, low, high, precision);
            break;
        case CONSTANT_SQRT2:
            if (method == METHOD_LIMIT) result = CalculateSqr2Limit(precision);
            else if (method == METHOD_SERIES) result = CalculateSqr2Series(precision);
            else result = CalculateRootUsingEquation(polinomSqrt2, low, high, precision);
            break;
        case CONSTANT_EULER_MASCHERONI:
            if (method == METHOD_LIMIT) result = CalculateYLimit(precision);
            else if (method == METHOD_SERIES) result = CalculateYSeries(precision);
            else result = CalculateRootUsingEquation(polinomEulerMascheroni, low, high, precision);
            break;
    }

    printf("Result: %.15f\n", result);
    return S_OK;
}
