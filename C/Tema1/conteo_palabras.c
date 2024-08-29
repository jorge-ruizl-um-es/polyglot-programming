# include <stdio.h>

/* programa para contar el numero de lineas, palabras y caracteres de una entrada por teclado */

# define IN 1   /* dentro de una palabra */
# define OUT 0  /* fuera de una palabra */

int main()
{
    int c, l, p, chr, state;

    state = OUT;
    l = p = chr = 0;

    while ((c=getchar()) != EOF){
        if (c == '\n')
            l++;    // contador de lineas - tantas lineas como saltos de linea haya
        
        if (c == ' ' || c == '\t' || c == '\n')
            state = OUT;    // detecta fin de una palabra
        
        else if (state == OUT){     // no es caracter de fin y estamos fuera de una palabra, significa que entramos a otra
            p ++;
            state = IN;
        }
        chr++;      // actualizar contador de caracteres
    }
    
    printf("Caracteres: %d \n Lineas: %d \n Palabras: %d \n", chr, l, p);

    return 0;
}

