# include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    // Utilizando valores de los headers estándar
    printf("Using standard headers:\n");
    printf("Signed char: %d to %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("Unsigned char: 0 to %u\n", UCHAR_MAX);
    printf("Signed short: %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("Unsigned short: 0 to %u\n", USHRT_MAX);
    printf("Signed int: %d to %d\n", INT_MIN, INT_MAX);
    printf("Unsigned int: 0 to %u\n", UINT_MAX);
    printf("Signed long: %ld to %ld\n", LONG_MIN, LONG_MAX);
    printf("Unsigned long: 0 to %lu\n", ULONG_MAX);
    printf("Float: %e to %e\n", FLT_MIN, FLT_MAX);
    printf("Double: %e to %e\n", DBL_MIN, DBL_MAX);

    // Calculando valores directamente
    printf("\nBy direct computation:\n");
    printf("Signed char: %d to %d\n", -(char)((unsigned char) ~0 >> 1) - 1, (char)((unsigned char) ~0 >> 1));
    printf("Unsigned char: 0 to %u\n", (unsigned char) ~0);
    printf("Signed short: %d to %d\n", -(short)((unsigned short) ~0 >> 1) - 1, (short)((unsigned short) ~0 >> 1));
    printf("Unsigned short: 0 to %u\n", (unsigned short) ~0);
    printf("Signed int: %d to %d\n", -(int)((unsigned int) ~0 >> 1) - 1, (int)((unsigned int) ~0 >> 1));
    printf("Unsigned int: 0 to %u\n", (unsigned int) ~0);
    printf("Signed long: %ld to %ld\n", -(long)((unsigned long) ~0 >> 1) - 1, (long)((unsigned long) ~0 >> 1));
    printf("Unsigned long: 0 to %lu\n", (unsigned long) ~0);

    return 0;

    /* explicacion del calculo directo: 

        hay que calcular el minimo y el maximo. en los unsigned sabemos que el minimo es 0
        
        limites inferiores:
            - en negativo, declaramos el tipo en general
            - ponemos (unsigned tipo) ~ 0 para convertir todos los 0 en 1 en su representación en bits
            - los desplazamos una posicion a la izquierda, de forma que se queda --> 01111...
            - le restamos 1
        
        limites superiores:
            - lo mismo pero sin restar 1, y en positivo
        */
}

