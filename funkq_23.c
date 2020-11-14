#include "odu_23.h"


double q(double x) {
    char message[CHAR_MAX];

    switch(example) {
        case 1: return 2 / (x * x + 1);
        case 2: return -4 / (2 * x + 1);
        case 3: return 2 / (x * x + 1);
        case 4: return 1 / (x * x * log(x));
        case 5: return (2 - x * tan(x)) / (x * x);
        case 6: return 10000;
        case 7: return (x * x + 3) / (x * x);
        default:
            sprintf(message, "Example %d does not exist", example);
            exception(message);
    }
}