#ifndef FINITE_DIFFERENCE_METHOD_ODU_23_H
#define FINITE_DIFFERENCE_METHOD_ODU_23_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int example, n;

void exception(char *message);

double p(double x);

double q(double x);

double f(double x);

double y(double x);

double first_derivative_of_y(double x);

double second_derivative_of_y(double x);

double *tridiagonal_matrix_algorithm(int n, const double *a, const double *b, const double *c, const double *f);

double *second_order_accurate_finite_difference_method(double left, double y_left, double y_right, double h);

double *pentadiagonal_matrix_algorithm(int n, const double *a, const double *b, const double *c, const double *d, const double *e, const double *f);

double *fourth_order_accurate_finite_difference_method(double left, double y_left, double y_left_next, double y_right_prev, double y_right, double h);

double *solve(double a, double b, double c, double d, double *h, double eps, int high_accuracy_approximation, double *error);

#endif //FINITE_DIFFERENCE_METHOD_ODU_23_H
