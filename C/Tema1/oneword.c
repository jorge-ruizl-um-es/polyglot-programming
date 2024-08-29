# include <stdio.h>

/* Programa que permite imprimir una frase introducida con una palabra por línea */

# define IN 1
# define OUT 0

int main()
{
    int state, c;

    state = IN;
    while ((c = getchar()) != EOF){
        if (c == ' ' || c == '\n' || c == '\t'){
            if (state==IN){
                putchar('\n');
                state=OUT;
            }
        }

        else{
            putchar(c);
            state = IN;
        }
    }

    return 0;
}