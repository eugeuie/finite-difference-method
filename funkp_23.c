#include "odu_23.h"


double p(double x) {
    char message[CHAR_MAX];

    switch(example) {
        case 1: return -2 * x / (x * x + 1);
        case 2: return 4 * x / (2 * x + 1);
        case 3: return -2 * x / (x * x + 1);
        case 4: return -1 / (x * log(x));
        case 5: return (x * tan(x) - 2) / x;
        case 6: return -1;
        case 7: return -(x * x + 3) / x;
        default:
            sprintf(message, "Example %d does not exist", example);
            exception(message);
    }
}