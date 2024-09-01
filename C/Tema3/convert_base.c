# include <stdio.h>
# include <string.h>

// funcion itob(n,s,b) para convertir int n a una representación de caracteres en base b dentro de la cadena s
// manejar el caso particular del hexadecimal

void itob(int n, char s[], int b);
void reverse(char s[]);

void itob(int n, char s[], int b)
{
    int i=0, sign;

    if ((sign=n)<0)
        n = -n;
    
    if (b>10){
        do {
            s[i++] = (n%b < 10) ? n%b + '0' : n%b - 10 +'A'; 
        } while ((n /= b) > 0);
    }
    else{
        do {
            s[i++] = n%b + '0';
        } while ((n /= b) > 0);
    }

    if (sign<0)
        s[i++] = '-';

    s[i] = '\0';
    reverse(s);
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
    int n = -12;
    char s[12000];

    itob(n, s, 16);
    printf("%s", s);
}