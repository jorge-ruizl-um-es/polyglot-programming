# include <stdio.h>

# define N 101

/* programa para, dado un array de enteros de longitud n, imprimirlo en lineas de 10 elementos. 
se debe imprimir un salto de linea tras el enesimo caracter tambien. usar la forma ?: del if-else*/

int main()
{
    int s[N];
    int i;

    for (i=0; i<N; ++i)
        s[i] = i;
    for (i=0; i<N; ++i)
        printf("%6d%c", s[i], (i%10==9 || i==N-1) ? '\n': ' ');

    return 0;
}