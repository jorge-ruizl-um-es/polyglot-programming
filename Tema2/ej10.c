# include <stdio.h>
# include <math.h>

/* programa para meter una funcion que convierta letras a minuscula */

int lower(int c)
{
    int salida;

    salida = (c>='A' && c<= 'Z') ? c+abs('a'-'A'): c;
    return salida;
}

int main()
{
    char s[] = "Hola Mundo";
    int i=0;

    while (s[i]!='\0'){
        printf("%c", lower(s[i++]));
    }
}