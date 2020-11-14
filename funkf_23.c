#include "odu_23.h"


double f(double x) {
    char message[CHAR_MAX];

    switch(example) {
        case 1: return 0;
        case 2: return 0;
        case 3: return x * x + 1;
        case 4: return -log(x);
        case 5: return x * exp(x) * cos(x);
        case 6: return 100 * exp(x) * cos(100 * x);
        case 7: return 10 * x * x * x * sin(x * x);
        default:
            sprintf(message, "Example %d does not exist", example);
            exception(message);
    }
}