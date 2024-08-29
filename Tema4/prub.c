# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <math.h>

# define NUMBER '0'

int getop(char s[]);
int getch(void);
void ungetch(int c);

int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c!='.')
        return c;   // es un operador
    i = 0;
    if (isdigit(c))     // reune la parte entera (ya se ha guardado de antes en s con el primer while)
        while(isdigit(c = getchar()))
            s[++i] = c;
    if (c=='.')     // reune la parte fraccionaria
        while (isdigit(c = getchar()))
            s[++i]=c;

    s[++i] = '\0';  // finaliza la cadena sustituyendo el último caracter leido y almacenado por null, ya que no es un digito
    return NUMBER;
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

int main()
{
    char s[] = "a";
    printf("%d", strlen(s));
}

