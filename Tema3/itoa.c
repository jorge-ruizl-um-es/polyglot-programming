# include <stdio.h>
# include <string.h>

// funcion itoa para convertir un entero a una cadena usando bucles do-while

void itoa(int n, char s[]);
void reverse(char s[]);

void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0)
        n = -n;     // si n es negativo, lo convertimos en positivo

    i = 0;
    do {
        s[i++] = n%10 + '0'; // Cogemos el digito de las unidades y le sumamos el ASCII de 0 para obtener el caracter
    } while ((n /= 10) > 0);    // vamos decrementando n a razón de 10 (desplazamos las unidades para ir obteniendo digito a digito)
    // el resultado del decremento es entero pq al ser int, se trunca
    // se parará cuando el resultado truncado sea 0

    if (sign < 0)
        s[i++]='-'; // añadimos el signo si es necesario
    s[i]='\0';
    reverse(s); // invertimos porque la hemos construido al reves (añadiamos las unidades al principio)
}

void reverse(char s[])
{
    int i, j, c;

    for (i=0, j=strlen(s)-1; i<j; i++, j--){
        c = s[i], s[i] = s[j], s[j] = c;
    }
}

int main()
{
    int n = -234;
    char s[12000];

    itoa(n, s);
    printf("%s", s);
}