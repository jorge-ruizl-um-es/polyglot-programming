#include <stdio.h>

#define N 2
#define MAXLEN 100000

/* programa con funcion entab para sustituir tres espacios consecutivos por una tabulación */

void entab(int len);
int getline(void);

char line[MAXLEN];

int main() {
    int len;

    while ((len = getline()) > 0) {
        entab(len);
    }

    return 0;
}

int getline(void) {
    int c, i = 0;

    while ((c = getchar()) != EOF && c != '\n' && i < MAXLEN - 1) {
        line[i] = c;
        ++i;
    }

    if (c == '\n') {
        line[i] = c;
        ++i;
    }

    line[i] = '\0';

    return i;
}

void entab(int len) {
    int i, space_count = 0;

    for (i = 0; i < len; i++) {
        if (line[i] == ' ') {
            space_count++;
            if (space_count == N) {
                putchar('t');
                space_count = 0;
            }
        } 
        else {
            /* si hay caracter no espacio, lo imprime tras imprimir espacios acumulados que no hayan llegado a formar tab*/
            while (space_count > 0) {
                putchar(' ');
                space_count--;
            }
            putchar(line[i]);
        }
    }

    /* Imprime los espacios acumulados al final de la ejecucion */
    while (space_count > 0) {
        putchar(' ');
        space_count--;
    }
}
