# include <stdio.h>
# include <string.h>

/* 
defincion de la funcion str_len, que devuelve la longitud de un array de caracteres

existe ya la función strlen en la biblioteca string.h
*/

# define FRASE "Hola mundo"

int str_len(char s[]);

int str_len(char s[])
{
    int i;

    i = 0;
    while (s[i] != '\0') {
        ++i;
    }

    return i;
}

int main() 
{
    printf("Longitud de FRASE con funcion definida manualmente: %d\n", str_len(FRASE));
    printf("Longitud de FRASE con strlen de la biblioteca estandar: %d\n", strlen(FRASE));

    return 0;
}