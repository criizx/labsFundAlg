#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void print_quadratic_result(int num_roots, double root1, double root2);
int solve_quadratic(double epsilon, double a, double b, double c, double* root1, double* root2);
int check_multiple(int num1, int num2);
int check_triangle(double epsilon, double a, double b, double c);

#endif
