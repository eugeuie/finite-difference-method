#include "odu_23.h"


double y(double x) {
    char message[CHAR_MAX];

    switch(example) {
        case 1: return 1 - x * x + 2 * x;
        case 2: return 3 * x + exp(-2 * x);
        case 3: return 1 - x * x + 2 * x - 11 * x + (x * x * x * x) / 6.0 + (x * x) / 2.0;
        case 4: return x + 2 * (log(x) + 1) + 0.5 * x * x * (1 - log(x));
        case 5: return x * (1 + sin(x)) + 0.5 * x * exp(x) * (cos(x) + sin(x));
//        case 6: return exp(x) * sin(x); // Invalid example
        case 7: return x * (1 + exp(0.5 * x * x)) + x * (cos(x * x) - 2 * sin(x * x));
        default:
            sprintf(message, "Example %d does not exist", example);
            exception(message);
    }
}

double first_derivative_of_y(double x) {
    char message[CHAR_MAX];

    switch (example) {
        case 1: return -2 * x + 2;
        case 2: return 3 - 2 * exp(-2 * x);
        case 3: return -x - 9 + 2 * (x * x * x) / 3;
        case 4: return 1 + 2 / x + 0.5 * x - x * log(x);
        case 5: return 1 + (x + exp(x) * (0.5 + x)) * cos(x) + (1 + 0.5 * exp(x)) * sin(x);
//        case 6: return exp(x) * (sin(x) + cos(x)); // Invalid example
        case 7: return 1 + exp(0.5 * x * x) + exp(0.5 * x * x) * x * x + (1 - 4 * x * x) * cos(x * x) - 2 * (1 + x * x) * sin(x * x);
        default:
            sprintf(message, "Example %d does not exist", example);
            exception(message);
    }
}

double second_derivative_of_y(double x) {
    char message[CHAR_MAX];

    switch (example) {
        case 1: return -2;
        case 2: return 4 * exp(-2 * x);
        case 3: return 2 * x * x - 1;
        case 4: return -2 / (x * x) - log(x) - 0.5;
        case 5: return (2 + exp(x) * (2 + x)) * cos(x) + (-1 - exp(x)) * x * sin(x);
//        case 6: return 2 * exp(x) * cos(x); // Invalid example
        case 7: return x * (exp(0.5 * x * x) * (x * x + 3) + (-4 * x * x - 12) * cos(x * x) + (8 * x * x - 6) * sin(x * x));
        default:
            sprintf(message, "Example %d does not exist", example);
            exception(message);
    }
}

double *tridiagonal_matrix_algorithm(int n, const double *a, const double *b, const double *c, const double *f) {
    int i;
    double z, alpha[n - 1], beta[n - 1], *x = malloc(n * sizeof(double));

    for(i = 0; i < n - 1; i++) {
        z = b[i] + a[i] * alpha[i - 1];
        alpha[i] = -c[i] / z;
        beta[i] = (f[i] - a[i] * beta[i - 1]) / z;
    }

    x[n - 1] = (f[n - 1] - a[n - 1] * beta[n - 2]) / (b[n - 1] + a[n - 1] * alpha[n - 2]);

    for (i = n - 2; i > -1; i--) {
        x[i] = alpha[i] * x[i + 1] + beta[i];
    }

    return x;
}

double *second_order_accurate_finite_difference_method(double left, double y_left, double y_right, double h) {
    int i;
    double x, *grid_y = malloc(n * sizeof(double)), *grid_y_without_borders, a[n - 2], b[n - 2], c[n - 2], g[n - 2];

    grid_y[0] = y_left;
    grid_y[n - 1] = y_right;

    for(i = 0, x = left + h; i < n - 2; i++, x += h) {
        a[i] = 1 / (h * h) - p(x) / (2 * h);
        b[i] = -2 / (h * h) + q(x);
        c[i] = 1 / (h * h) + p(x) / (2 * h);
        g[i] = f(x);
    }

    g[0] -= a[0] * grid_y[0];
    a[0] = 0;
    g[n - 3] -= c[n - 3] * grid_y[n - 1];
    c[n - 3] = 0;

    grid_y_without_borders = tridiagonal_matrix_algorithm(n - 2, a, b, c, g);

    for(i = 1; i < n - 1; i++) {
        grid_y[i] = grid_y_without_borders[i - 1];
    }

    free(grid_y_without_borders);
    return grid_y;
}

double *pentadiagonal_matrix_algorithm(int n, const double *a, const double *b, const double *c, const double *d, const double *e, const double *f) {
    int i;
    double z, alpha[n - 1], beta[n - 2], gamma[n - 1], *x = malloc(n * sizeof(double));

    for(i = 0; i < n - 2; i++) {
        z = a[i] * alpha[i - 2] * alpha[i - 1] + a[i] * beta[i - 2] + b[i] * alpha[i - 1] + c[i];
        alpha[i] = -(a[i] * alpha[i - 2] * beta[i - 1] + b[i] * beta[i - 1] + d[i]) / z;
        beta[i] = -e[i] / z;
        gamma[i] = (f[i] - (a[i] * alpha[i - 2] * gamma[i - 1] + a[i] * gamma[i - 2] + b[i] * gamma[i - 1])) / z;
    }

    z = a[n - 2] * alpha[n - 4] * alpha[n - 3] + a[n - 2] * beta[n - 4] + b[n - 2] * alpha[n - 3] + c[n - 2];
    alpha[n - 2] = -(a[n - 2] * alpha[n - 4] * beta[n - 3] + b[n - 2] * beta[n - 3] + d[n - 2]) / z;
    gamma[n - 2] = (f[n - 2] - (a[n - 2] * alpha[n - 4] * gamma[n - 3] + a[n - 2] * gamma[n - 4] + b[n - 2] * gamma[n - 3])) / z;

    x[n - 1] = (f[n - 1] - (a[n - 1] * alpha[n - 3] * gamma[n - 2] + a[n - 1] * gamma[n - 3] + b[n - 1] * gamma[n - 2]))
            / (a[n - 1] * alpha[n - 3] * alpha[n - 2] + a[n - 1] * beta[n - 3] + b[n - 1] * alpha[n - 2] + c[n - 1]);
    x[n - 2] = alpha[n - 2] * x[n - 1] + gamma[n - 2];

    for(i = n - 3; i > -1; i--) {
        x[i] = alpha[i] * x[i + 1] + beta[i] * x[i + 2] + gamma[i];
    }

    return x;
}

double *fourth_order_accurate_finite_difference_method(double left, double y_left, double y_left_next, double y_right_prev, double y_right, double h) {
    int i;
    double x, *grid_y = malloc(n * sizeof(double)), *grid_y_without_borders, a[n - 4], b[n - 4], c[n - 4], d[n - 4], e[n - 4], g[n - 4];

    grid_y[0] = y_left;
    grid_y[1] = y_left_next;
    grid_y[n - 2] = y_right_prev;
    grid_y[n - 1] = y_right;

    for(i = 0, x = left + 2 * h; i < n - 4; i++, x += h) {
        a[i] = -1 / (12 * h * h) + p(x) / (12 * h);
        b[i] = 16 / (12 * h * h) - (8 * p(x)) / (12 * h);
        c[i] = -30 / (12 * h * h) + q(x);
        d[i] = 16 / (12 * h * h) + (8 * p(x)) / (12 * h);
        e[i] = -1 / (12 * h * h) - p(x) / (12 * h);
        g[i] = f(x);
    }

    g[0] -= b[0] * grid_y[1] + a[0] * grid_y[0];
    a[0] = 0;
    b[0] = 0;
    g[1] -= a[1] * grid_y[1];
    a[1] = 0;
    g[n - 6] -= e[n - 6] * grid_y[n - 2];
    e[n - 6] = 0;
    g[n - 5] -= d[n - 5] * grid_y[n - 2] + e[n - 5] * grid_y[n - 1];
    d[n - 5] = 0;
    e[n - 5] = 0;

    grid_y_without_borders = pentadiagonal_matrix_algorithm(n - 4, a, b, c, d, e, g);

    for(i = 2; i < n - 2; i++) {
        grid_y[i] = grid_y_without_borders[i - 2];
    }

    free(grid_y_without_borders);
    return grid_y;
}

double loss(double left, double h, double *grid_y) {
    int i;
    double loss = 0, x;

    for(i = 0, x = left; i < n; i++, x += h) {
        loss += pow(y(x) - grid_y[i], 2);
    }
    loss /= n;

    return loss;
}

double *solve(double a, double b, double c, double d, double *h, double eps, int high_accuracy_approximation, double *error) {
    char message[CHAR_MAX];
    double *grid_y, c_next, d_prev;

    while(1) {
//        if(*h <= 2e-5) {
//            sprintf(message, "Too small step. Try to increase the value of allowable error (eps), minimum possible value is 1e-016, yours is %1.0e", eps);
//            exception(message);
//        }

        n = (int) ((b - a) / *h) + 1;

        if(!high_accuracy_approximation) {
            grid_y = second_order_accurate_finite_difference_method(a, c, d, *h);
        } else {
            c_next = y(a + *h);
            d_prev = y(b - *h);
            grid_y = fourth_order_accurate_finite_difference_method(a, c, c_next, d_prev, d, *h);
        }

        *error = loss(a, *h, grid_y);
        printf("example %d: step %.16lf, error %.16lf\n", example, *h, *error);

        if(*error < eps) break;
        *h /= 2;
    }

    return grid_y;
}
