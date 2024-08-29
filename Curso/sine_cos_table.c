#include <stdio.h>
#include <math.h>
// we include this header to use the sin and cosine functions


int main(void) {
    // in the exercise, the interval is open, so we do not include 0 nor 1
    double number = 0.1;

    while (number <= 0.9) {     // we increment number in 0.1 until reaching 0.9
        printf("sin(%1.1lf) = %.5lf \t cos(%1.1lf) = %.5lf \n", number, sin(number), number, cos(number));
        number += 0.1;
    }
    return 0;
}