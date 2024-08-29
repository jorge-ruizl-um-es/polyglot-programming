# include <stdio.h>

void main()
{
    int c, g;

    /* Forma larga:

    c = getchar();
    while (c != EOF){
        putchar(c);
        c = getchar();
    }
    */

   // prueba de un comentario de una sola linea

    while ((c=getchar()) != EOF)
        putchar(c);

    printf("%d", getchar() != EOF); /* Esto lee una entrada por teclado sin almacenarla, la compara con EOF 
                                    y devuelve 1 si lo que metes es distintos, 0 si es igual*/

}