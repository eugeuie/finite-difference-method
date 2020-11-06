#ifndef FINITE_DIFFERENCE_METHOD_ODU_23_H
#define FINITE_DIFFERENCE_METHOD_ODU_23_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int example, message_size, n;

void exception(char *message);

double p(double x);

double q(double x);

double f(double x);

double y(double x);

double first_derivative_of_y(double x);

double second_derivative_of_y(double x);

double *tridiagonal_matrix_algorithm(int n_equations, const double *a, const double *b, const double *c, const double *d);

double *finite_difference_method(double left, double y_left, double y_right, double h);

#endif //FINITE_DIFFERENCE_METHOD_ODU_23_H
