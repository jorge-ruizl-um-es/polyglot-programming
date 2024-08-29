# include <stdio.h>
# include <ctype.h>

/* funcion htoi(s) para convertir una cadena de digitos hexadecimales de la forma "0xHHH" en su valor entero decimal */

int htoi(char s[]);
int lower(char c);

int lower(char c)
{
    if (c>='A' && c<='Z')
        return c + 'a' - 'A';
    else
        return c;
}

int htoi(char s[])
{
    int result, i, l;

    result = i = 0;

    while (s[i]!='\0' && s[i]!='\n')
    {
        l = lower(s[i]);
        if (i == 0 && s[0]=='0' && s[1]=='x')
            ++i;
        else if (l>='a' && l<='f')
            result = 16*result + (l - 'a' + 10);
        else if (isdigit(l))
            result = 16*result + (l - '0');
        else {
            printf("Cadena en hexadecimal invalida\n");
            result = -1;
        }
        ++i;
    }

    return result;
}

int main() 
{
    char s[] = "0x31FA";

    printf("%d", htoi(s));
}