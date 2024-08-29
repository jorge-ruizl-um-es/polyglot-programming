# include <ctype.h>
# include <stdio.h>

# define SIZE 1000

int getch(void);
void ungetch(int);
/* getint: obtiene el siguiente entero de la entrada y lo asigna a *pn */

int getint(int *pn) {
    int c, sign;    
    while (isspace(c = getch())) /* ignora espacios en blanco */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        return 0;
    }
    sign = (c == '-') ? - 1 : 1 ;

    if (c == '+' || c == '-')
        c = getch();
    for (*pn = 0 ; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}

int main() {
    int n, *i, array[SIZE], out;
    for (n = 0; n < SIZE && (out = getint(&array[n])) != EOF;) {
        if (out==0)
            ;
        else
            n++;
    }
    printf("%d\n", n);
    for (i=array; i<SIZE+array; i++)
        printf("%d ", *i);
    return 0;
}

# define BUFSIZE 100

char buffer[BUFSIZE];
int bufp = 0;   // siguiente posicion vacia del buffer

int getch(void)
{
    return (bufp>0) ? buffer[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp>=BUFSIZE)  
        printf("Error en ungetch");
    else
        buffer[bufp++] = c;
}
