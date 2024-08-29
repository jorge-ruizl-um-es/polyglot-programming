#include<stdio.h>
#include<math.h> /* has  sin(), abs(), and fabs() */

int main(void) { 
    double interval;
    int i;

    for(i = 0; i<30; i++)  {
        interval = i/10.0;
        printf("sin(%1.1lf) = %.3lf \t", interval, fabs(sin(interval)));
        // we're using "fabs" for getting the absolute value of a floating point number
    }

    printf("\n+++++++\n");
    return 0;
}