#include <stdio.h>

/* Programa que devuelve la entrada que se le pasa, pero sustituyendo todos los espacios consecutivos por uno*/

# define SPACE 1
# define NOTSPACE 0

int main()
{
    int c, status;

    status = NOTSPACE;

    while ((c=getchar()) != EOF){
        if (c == ' '){
            if (status == NOTSPACE){
                putchar(c);
                status = SPACE;
            }
        }
        else {
            putchar(c);
            status = NOTSPACE;
        }
    }
}