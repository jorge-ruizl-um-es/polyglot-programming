# include <stdio.h>

/* funcion atoi para convertir s en un entero */

int atoi(char s[]);
int lower(int c);

int atoi(char s[])
{
    int i, n;

    n = 0;

    for (i=0; s[i]>='0' && s[i]<='9'; ++i)
        n = 10*n + (s[i]-'0');

    return n;
}

int lower(int c)
{
    int salida;

    if (c>='A' && c<='Z')
        salida = c + 'a' - 'A';
    else
        salida = c;
    return salida;
}

int main() 
{
    char s[] = "456";
    char c = 'D';

    printf("%d", atoi(s)); 
    printf("%c", lower(c));
}