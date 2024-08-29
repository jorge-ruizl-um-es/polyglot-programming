# include <stdio.h>
# define MAXLEN 1000

/* programa para leer lineas introducidas por teclado y devolver al final de la ejecucion la mas larga */

/* declaración de funciones */

int getline(char line[], int maxlen);
void copy(char to[], char from[]);

/* char line[] define un array de caracteres */

int main()
{
    int len, max;
    char line[MAXLEN];
    char longest[MAXLEN];

    max = 0;
    while ((len = getline(line, MAXLEN)) > 0){ /* lee la linea correspondiente y la recupera */
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    }

    if (max>0)
        printf("%s", longest);
    return 0; /* devuelve 0 si no hay ninguna linea */
}

/* funcion getline para leer una linea y devolver su longitud */

int getline(char s[], int lim) /* no hace falta definir tamaño de s porque ya está definido en main */
{
    int c, i;

    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n'){
        s[i] = c; /* el fin de linea cuenta como caracter */
        ++i;
    }
    s[i] = '\0'; /* al final de una linea metemos el caracter nulo */
    return i;
}

/* funcion copy para copiar en to el contenido de from*/

void copy(char to[], char from[])
{
    int i = 0;

    while ((to[i]=from[i])!='\0')
        i++;
}


