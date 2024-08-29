#include <stdio.h>

/* imprime la tabla de equivalencias Fahrenheit-Celsius
    para fahr = 0, 20, ..., 300 */


float Fahr_Cel(int fahr)
{
    return (5.0/9.0)*(fahr-32.0);
}

int main()
{
    float fahr, celsius, fahr2, celsius2;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    printf("Tabla de conversion Fahrenheit-Celsius:\n");
    while(fahr <= upper) {
        celsius = Fahr_Cel(fahr);
        printf("%3.0f\t%6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }

    printf("\n");

    celsius2 = lower;
    printf("Tabla de conversion Celsius-Fahrenheit:\n");
    while(celsius2 <= upper) {
        fahr2 = (9.0/5.0)*(celsius2)+32;
        printf("%3.0f \t %6.1f \n", celsius2, fahr2);
        celsius2 = celsius2 + step;
    }

}