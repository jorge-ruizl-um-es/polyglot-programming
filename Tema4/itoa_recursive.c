# include <stdio.h>

/*
Funcion printd para imprimir un entero en base 10.
Le daremos un enfoque recursivo: la funcion irá llamandose a sí misma hasta alcanzar la posicion final
*/

static char array[1000];
static int array_index = 0;

void printd(int i) {
    if (i<0) {      // manejo de negativos
        array[array_index++] = '-';   
        i = -i;    // una vez ponemos el signo, lo convertimos a positivo para que no afecte al resto de llamadas
    }
    if (i/10 != 0) {     // condicion de parada
        printd(i/10);
    }
    array[array_index++] = i%10 + '0';
}

int main() {
    printd(-29982);
    array[array_index] = '\0';
    printf("%s\n", array);
    return 0;
}