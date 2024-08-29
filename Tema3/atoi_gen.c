# include <stdio.h>
# include <ctype.h>

// funcion de conversion de cadena a entero general --> ignora espacios en blanco y toma el signo
int atoi(char s[]);

int atoi(char s[])
{
    int i, sign, result = 0;

    for (i=0; isspace(s[i]); ++i)
        ;   // ignorar
    
    sign = (s[i]=='-')? -1 : 1; // el siguiente al último espacio será el signo si lo hay

    if (s[i] == '+' || s[i] =='-')
        ++i;    // una vez tomado el signo, ignorar (pasar al siguiente caracter)

    while (s[i]!='\0' && isdigit(s[i])){
        result = 10*result + (s[i]-'0');
        ++i;
    }
    result *= sign;
    return result;
}

int main() 
{
    char s[] = "   -456";

    printf("%d", atoi(s));
}
