#include <time.h>
#include "odu_23.h"


void exception(char *message) {
    printf("%s\n", message);
    exit(1);
}

void get_input(int read_from_file, char *filename, double *a, double *b, double *c, double *d, double *h, double *eps) {
    char message[message_size];

    if(read_from_file) {
        FILE *input_file;

        if((input_file = fopen(filename, "r")) == NULL) {
            sprintf(message, "Cannot open input file");
            exception(message);
        }

        fscanf(input_file, "%lf %lf %lf %lf %lf %lf", a, b, c, d, h, eps);
    } else {
        switch(example) {
            case 1: *a = 0,     *b = 1;     break;
            case 2: *a = 0,     *b = 2;     break;
            case 3: *a = 0,     *b = 3;     break;
            case 4: *a = 2,     *b = 5;     break;
            case 5: *a = 0.5,   *b = 1.5;   break;
            case 6: *a = 0,     *b = 1;     break;
            case 7: *a = 1,     *b = 2;     break;
            default:
                sprintf(message, "Example %d does not exist", example);
                exception(message);
        }

        *c = y(*a);
        *d = y(*b);
        *h = 0.001;
        *eps = 0.001;
    }
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

void print_output(double left, double right, double h, double eps, double *grid_y,
                  int save_to_png, double time, int n_nodes, double loss) {
    int i;

    char result_filename[] = "../results/#_example_output.txt";
    char info_filename[] = "../results/#_example_info.txt";
    result_filename[11] = '0' + example;
    info_filename[11] = '0' + example;

    FILE *result_file = fopen(result_filename, "w");
    for(i = 0; i < n; i++) {
        fprintf(result_file, "%lf\n", grid_y[i]);
    }

    FILE *info_file = fopen(info_filename, "w");
    fprintf(info_file, "time:\t%lf\n", time);
    fprintf(info_file, "step:\t%lf\n", h);
    fprintf(info_file, "eps:\t%lf\n", eps);
    fprintf(info_file, "nodes:\t%d\n", n_nodes);
    fprintf(info_file, "loss:\t%lf\n", loss);

    draw(left, right, h, grid_y, save_to_png);
}

int main() {
    message_size = 256;
//    example = 1;
    clock_t start, end;
    double a, b, c, d, h, eps;

    for(example = 1; example <= 7; example++) {
        get_input(0, "../input.txt", &a, &b, &c, &d, &h, &eps);
        n = (int) ((b - a) / h) + 1;
        double *grid_y;

        start = clock();
        grid_y = finite_difference_method(a, b, c, d, h, eps);
        end = clock();

        print_output(a, b, h, eps, grid_y, 1, ((double) (end - start) / CLOCKS_PER_SEC), n, loss(a, h, grid_y));
    }

//    get_input(0, "../input.txt", &a, &b, &c, &d, &h, &eps);
//    n = (int) ((b - a) / h) + 1;
//    double *grid_y;
//
//    start = clock();
//    grid_y = finite_difference_method(a, b, c, d, h, eps);
//    end = clock();
//
//    print_output(a, b, h, eps, grid_y, 1, ((double) (end - start) / CLOCKS_PER_SEC), n, loss(a, h, grid_y));

    return 0;
}
