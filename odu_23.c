#include "odu_23.h"


double y(double x) {
    char message[message_size];

    switch(example) {
        case 1: return 1 - x * x + 2 * x;
        case 2: return 3 * x + exp(-2 * x);
        case 3: return 1 - x * x + 2 * x - 11 * x + (x * x * x * x) / 6.0 + (x * x) / 2.0;
        case 4: return x + 2 * (log(x) + 1) + 0.5 * x * x * (1 - log(x));
        case 5: return x * (1 + sin(x)) + 0.5 * x * exp(x) * (cos(x) + sin(x));
        case 6: return exp(x) * sin(x);
        case 7: return x * (1 + exp(0.5 * x * x)) + x * (cos(x * x) - 2 * sin(x * x));
        default:
            sprintf(message, "Example %d does not exist", example);
            exception(message);
    }
}

double first_derivative_of_y(double x) {
    char message[message_size];

    switch (example) {
        case 1: return -2 * x + 2;
        case 2: return 3 - 2 * exp(-2 * x);
        case 3: return -x - 9 + 2 * (x * x * x) / 3;
        case 4: return 1 + 2 / x + 0.5 * x - x * log(x);
        case 5: return 1 + (x + exp(x) * (0.5 + x)) * cos(x) + (1 + 0.5 * exp(x)) * sin(x);
        case 6: return exp(x) * (sin(x) + cos(x));
        case 7: return 1 + exp(0.5 * x * x) + exp(0.5 * x * x) * x * x + (1 - 4 * x * x) * cos(x * x) - 2 * (1 + x * x) * sin(x * x);
        default:
            sprintf(message, "Example %d does not exist", example);
            exception(message);
    }
}

double second_derivative_of_y(double x) {
    char message[message_size];

    switch (example) {
        case 1: return -2;
        case 2: return 4 * exp(-2 * x);
        case 3: return 2 * x * x - 1;
        case 4: return -2 / (x * x) - log(x) - 0.5;
        case 5: return (2 + exp(x) * (2 + x)) * cos(x) + (-1 - exp(x)) * x * sin(x);
        case 6: return 2 * exp(x) * cos(x);
        case 7: return x * (exp(0.5 * x * x) * (x * x + 3) + (-4 * x * x - 12) * cos(x * x) + (8 * x * x - 6) * sin(x * x));
        default:
            sprintf(message, "Example %d does not exist", example);
            exception(message);
    }
}

double *tridiagonal_matrix_algorithm(int n_equations, const double *a, const double *b, const double *c, const double *d) {
    int i;
    double alpha[n_equations - 1], beta[n_equations], *x = malloc(n_equations * sizeof(double));

    for(i = 0; i < n_equations - 1; i++) {
        alpha[i] = -c[i] / (b[i] + a[i] * alpha[i - 1]);
        beta[i] = (d[i] - a[i] * beta[i - 1]) / (b[i] + a[i] * alpha[i - 1]);
    }

    x[n_equations - 1] = (d[n_equations - 1] - a[n_equations - 1] * beta[n_equations - 2]) / (b[n_equations - 1] + a[n_equations - 1] * alpha[n_equations - 2]);

    for (i = n_equations - 2; i > -1; i--) {
        x[i] = alpha[i] * x[i + 1] + beta[i];
    }

    return x;
}

double *finite_difference_method(double left, double right, double y_left, double y_right, double h, double eps) {
    int i;
    double x, *y = malloc(n * sizeof(double)), *y_without_borders, a[n - 2], b[n - 2], c[n - 2], d[n - 2];

    y[0]     = y_left;
    y[n - 1] = y_right;

    for(i = 0, x = left + h; i < n - 2; i++, x += h) {
        a[i] = 1 / (h * h) - p(x) / (2 * h);
        b[i] = -2 / (h * h) + q(x);
        c[i] = 1 / (h * h) + p(x) / (2 * h);
        d[i] = f(x);
    }

    d[0]     -= a[0] * y[0];            a[0]     = 0;
    d[n - 3] -= c[n - 3] * y[n - 1];    c[n - 3] = 0;

    y_without_borders = tridiagonal_matrix_algorithm(n - 2, a, b, c, d);

    for(i = 1; i < n - 1; i++) {
        y[i] = y_without_borders[i - 1];
    }

    return y;
}
