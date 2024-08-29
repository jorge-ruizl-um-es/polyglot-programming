# include <stdio.h>

/*
Versión recursiva de itoa para convertir un entero a una cadena apoyándonos de printd
*/

static char s[10000];
static int i = 0;

void itoa_rec(int n) {
    if (n<0) {
        s[i++] = '-';
        n = -n;
    }

    if (n/10 != 0)
        itoa_rec(n/10);
    s[i++] = n%10+'0';
}

int main() {
    itoa_rec(-234);
    printf("%s", s);
}