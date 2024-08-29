#include <stdio.h>
#include <math.h>
// we include this header to use the sin function


int main(void) { 
    double input_number;

    printf("Enter a number between 0 and 1 (non inclusive):");
    scanf("%lf", &input_number);


    if (input_number>0 && input_number<1) {
        printf("\nThe sine of %lf is: sin(%lf) = %lf\n", input_number, input_number, sin(input_number));
        return 0;   // correct execution
    }
    else {
        printf("The number is out of range");
        return -1;     // error
    }
}