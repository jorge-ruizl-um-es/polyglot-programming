#include <stdio.h>

int modulo(int a, int b);

int main() {
    int a, b;
    printf("Introduce el dividendo: ");
    scanf("%d", &a);
    printf("Introduce el divisor: ");
    scanf("%d", &b);

    int result = modulo(a, b);
    printf("El resultado de %d %% %d es: %d\n", a, b, result);

    return 0;
}

int modulo(int a, int b) {
    if (b == 0) {
        // El comportamiento de % con divisor 0 no está definido,
        // aquí manejamos el caso especial
        printf("Error: División por cero\n");
        return 0; // Retornamos 0 por simplicidad, pero puede manejarse de otra forma
    }

    int r = a - (a/b)*b;

    // Si el resultado es negativo y el dividendo es negativo, ajustamos el resultado
    if (r < 0 && a < 0) {
        r += b;
    }

    return r;
}