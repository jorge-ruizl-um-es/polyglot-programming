# include <stdio.h>
# define lim 1000

/* 
escribir un ciclo equivalente a :

for (i = 0; i < lim-1 && (c = getchar( )) != '\n' && c != EOF; ++i)
s[i] = c;

sin usar los operadores && y ||
*/

int main() {

    int i, c;
    char s[1000];

    i = 0;

    while (i < lim-1) {
        c = getchar();
        if (c == '\n')
            break;
        if (c == EOF)
            break;
        s[i] = c;
        ++i;
    }
    s[i] = '\n';
    s[++i] = '\0';

    printf("%s", s);
}