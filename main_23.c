// Задача 23: Конечно-разностный метод с использованием метода аппроксимации функции для решения уравнений

#include <time.h>
#include "odu_23.h"


void exception(char *message) {
    printf("%s\n", message);
    exit(1);
}

void draw(double left, double right, double h, double *grid_y, int save_to_png) {
    int i;
    double x;
    FILE *pipe = popen("gnuplot -persistent", "w");

    if(save_to_png) {
        fprintf(pipe, "set terminal png\n");
        fprintf(pipe, "set output '../results/%d_example_plot.png'\n", example);
    }
    fprintf(pipe, "set key box opaque\n");
    fprintf(pipe, "plot '-' with linespoints pointtype 0 lw 6 lt rgb \"blue\"  title 'source function'");
    fprintf(pipe, " , '-' with linespoints pointtype 0 lw 3 lt rgb \"orange\" title 'approximation'\n");

    for(x = left; x < right; x += 0.0001) {
        fprintf(pipe, "%lf %lf\n", x, y(x));
    }
    fprintf(pipe, "%s\n", "e");
    fflush(pipe);

    for(i = 0, x = left; i < n; i++, x += h){
        fprintf(pipe, "%lf %lf\n", x, grid_y[i]);
    }
    fprintf(pipe, "%s\n", "e");
    fflush(pipe);

    pclose(pipe);
}

void input(int read_from_file, char *filename, double *a, double *b, double *c, double *d, double *h, double *eps) {
    char message[CHAR_MAX];

    if(read_from_file) {
        FILE *input_file;

        if((input_file = fopen(filename, "r")) == NULL) {
            sprintf(message, "Cannot open input file");
            exception(message);
        }

        fscanf(input_file, "%lf %lf %lf %lf %lf %lf", a, b, c, d, h, eps);
        fclose(input_file);
    } else {
        switch(example) {
            case 1: *a = 0,     *b = 1;     break;
            case 2: *a = 0,     *b = 2;     break;
            case 3: *a = 0,     *b = 3;     break;
            case 4: *a = 2,     *b = 5;     break;
            case 5: *a = 0.5,   *b = 1.5;   break;
//            case 6: *a = 0,     *b = 1;     break; // Invalid example
            case 7: *a = 1,     *b = 2;     break;
            default:
                sprintf(message, "Example %d does not exist", example);
                exception(message);
        }

        *c = y(*a);
        *d = y(*b);
        *h = 0.1;
        *eps = 1e-16;
    }
}

void output(double left, double right, double h, double eps, double *grid_y,
            int save_to_png, double time, int n_nodes, double loss) {
    int i;

    char result_filename[] = "../results/#_example_output.txt";
    char info_filename[] = "../results/#_example_info.txt";
    result_filename[11] = '0' + example;
    info_filename[11] = '0' + example;

    FILE *result_file = fopen(result_filename, "w");
    fprintf(result_file, "%d\n", n_nodes);
    for(i = 0; i < n; i++) {
        fprintf(result_file, "%lf\n", grid_y[i]);
    }

    FILE *info_file = fopen(info_filename, "w");
    fprintf(info_file, "time:\t%.7lf\n", time);
    fprintf(info_file, "step:\t%.7lf\n", h);
    fprintf(info_file, "nodes:\t%d\n", n_nodes);
    fprintf(info_file, "eps:\t%1.2e\n", eps);
    fprintf(info_file, "loss:\t%1.2e\n", loss);

    draw(left, right, h, grid_y, save_to_png);

    fclose(result_file);
    fclose(info_file);
}

int main() {
    clock_t start, end;
    double a, b, c, d, h, eps, *grid_y, error = INFINITY;

    example = 1; // 6th example is invalid

    input(0, "../input.txt", &a, &b, &c, &d, &h, &eps);

    start = clock();
    grid_y = solve(a, b, c, d, &h, eps, 0, &error);
    end = clock();

    output(a, b, h, eps, grid_y, 0, ((double) (end - start) / CLOCKS_PER_SEC), n, error);
    free(grid_y);

//    for(example = 1; example <= 7; example++) {
//        double a, b, c, d, h, eps, *grid_y, error = INFINITY;
//
//        if(example == 6) continue; // 6th example is invalid
//
//        input(0, "../input.txt", &a, &b, &c, &d, &h, &eps);
//
//        start = clock();
//        grid_y = solve(a, b, c, d, &h, eps, 1, &error);
//        end = clock();
//
//        output(a, b, h, eps, grid_y, 1, ((double) (end - start) / CLOCKS_PER_SEC), n, error);
//
//        free(grid_y);
//    }

    return 0;
}
