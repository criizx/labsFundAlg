#include <stdio.h>
#include <math.h>
#include "polynomials.h"
#include "root_finder.h"

int main() {
    double a, b, eps, x;
    int choice;
    double (*polinom)(double);

    printf("Choose a constant to find the root for:\n");
    printf("1. e\n");
    printf("2. π\n");
    printf("3. ln(2)\n");
    printf("4. sqrt(2)\n");
    printf("Enter the constant number: ");
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
        printf("Input error!\n");
        return 1;
    }

    switch (choice) {
        case 1:
            polinom = polinomE;
            break;
        case 2:
            polinom = polinomPi;
            break;
        case 3:
            polinom = polinomLn2;
            break;
        case 4:
            polinom = polinomSqrt2;
            break;
        default:
            printf("Invalid choice!\n");
            return 1;
    }

    printf("Enter the interval bounds (a and b): ");
    if (scanf("%lf %lf", &a, &b) != 2) {
        printf("Input error!\n");
        return 1;
    }

    if (polinom(a) * polinom(b) > 0) {
        printf("Invalid interval! The function has the same signs at the ends.\n");
        return 1;
    }

    printf("Enter precision (eps): ");
    if (scanf("%lf", &eps) != 1) {
        printf("Input error!\n");
        return 1;
    }

    x = findRoot(polinom, a, b, eps);
    printf("Root: %lf\n", x);

    return 0;
}
