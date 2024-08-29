# include <stdio.h>

/* funcion swap con punteros para intercambiar los valores de las variables de la llamada y no de copias */

void swap (int *px, int *py) {
    int _temp;

    _temp = *px; // temp almacena el valor de la variable a la que apunta px
    *px = *py;  // el valor de la variable a la que apunta px ahora será el de la variable a la que apunta py
    *py = _temp;  // viceversa
}

int main() {
    int a = 4, b = 9;
    swap(&a, &b);   // más eficiente
    printf("Valor de a = %d; valor de b = %d", a, b);   
    return 0;
}