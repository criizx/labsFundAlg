#include <stdio.h>
#include <math.h>

double polinom_(double x) {
    double e = exp(1.0);
     return x * x - 2;
}

double findRoot(double (*polinom)(double), double a, double b, double eps) {
    double c;
    while ((b - a) / 2 > eps) {
        c = (a + b) / 2;
        if (polinom(a) * polinom(c) > 0) {
            a = c;
        } else {
            b = c;
        }
    }
    return c;
}

int main() {
    double a, b, eps, x;

    printf("Введите границы интервала (a и b): ");
    if (scanf("%lf %lf", &a, &b) != 2) {
        printf("Ошибка ввода!\n");
        return 1;
    }

    if (polinom(a) * polinom(b) > 0) {
        printf("Неверный интервал!\n");
        return 0;
    }

    printf("Введите точность (eps): ");
    if (scanf("%lf", &eps) != 1) {
        printf("Ошибка ввода!\n");
        return 1;
    }

    x = findRoot(polinom, a, b, eps);
    printf("Корень: %lf\n", x);

    return 0;
}
