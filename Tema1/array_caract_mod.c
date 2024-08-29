# include <stdio.h>
# define MAXLEN 10

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
        printf("La linea mas larga es: %s\n", longest);
        printf("La longitud real de la linea es: %d", max);

    return 0; /* devuelve 0 si no hay ninguna linea */
}

/* funcion getline para leer una linea y devolver su longitud */

int getline(char s[], int lim) /* no hace falta definir tamaño de s porque ya está definido en main */
{
    int c, i;
    int total_len;

    total_len = 0;

    for (i=0; (c=getchar())!=EOF && c!='\n'; ++i){
        if (i<lim-1)
            s[i] = c;
        ++total_len;
    }

    if (c == '\n'){
        s[i] = c; /* el fin de linea cuenta como caracter */
        ++i;
        ++total_len;
    }
    s[i] = '\0'; /* al final de una linea metemos el caracter nulo */
    return total_len;
}

/* funcion copy para copiar en to el contenido de from*/

void copy(char to[], char from[])
{
    int i;

    i = 0;

    while ((to[i]=from[i])!='\0')
        i++;
}


