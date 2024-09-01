# include <stdio.h>

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
