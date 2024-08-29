# include <stdio.h>
# include <string.h>

// version de itoa que acepte 3 argumentos, siendo uno de ellos el ancho minimo del campo, de forma que al numero convertido se le 
// añaden espacios en blanco a la izquierda hasta cubrir el ancho minimo

void itoa(int n, char s[], int a);
void reverse(char s[]);

void itoa(int n, char s[], int a)
{
    int i, sign;

    if ((sign = n) < 0)
        n = -n;     // si n es negativo, lo convertimos en positivo

    i = 0;
    do {
        s[i++] = n%10 + '0'; // Cogemos el digito de las unidades y le sumamos el ASCII de 0 para obtener el caracter
    } while ((n /= 10) > 0);    // vamos decrementando n a razón de 10 (desplazamos las unidades para ir obteniendo digito a digito)
    // el resultado del decremento es entero pq al ser int, se trunca
    // se parara cuando el resultado truncado sea 0

    if (sign < 0)
        s[i++]='-'; // añadimos el signo si es necesario
    while (strlen(s)<a) {
        s[i++] = ' ';
    }
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

    itoa(n, s, 3);
    printf("%s", s);
}