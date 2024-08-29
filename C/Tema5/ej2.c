# include <stdio.h>
# include <ctype.h>

# define SIZE 100

int getch(void);
void ungetch(int);

int getfloat (float *pf) {
    int c, sign;
    float power;

    while (isspace(c = getch()))
        ;
    
    if (!isdigit(c) && c!='-' && c!='+' && c!=EOF) {
        return 0;
    }

    sign = (c=='-') ? -1 : 1;
    if (c == '+' || c ==  '-') {
        c = getch();
    }
    for (*pf=0; isdigit(c); c = getch()) {
        *pf = 10 * *pf + (c - '0');
    }
    if (c=='.') {
        c = getch();
    }
    for (power = 1.0; isdigit(c); c = getch()) {
        *pf = 10 * *pf + (c-'0');
        power *= 10.0;
    }
    *pf = sign * (*pf/power);
    if (c != EOF)
        ungetch(c);
    return c; 
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

int main() {
    int n, i, out;
    float array[SIZE];
    for (n = 0; n < SIZE && (out = getfloat(&array[n])) != EOF;) {  // también se podría pasar array+n
        if (out==0)
            ;
        else
            n++;
    }
    printf("%d\n", n);
    for (i=0; i<n; i++)
        printf("%.3f ", array[i]);
    return 0;
}