# include <stdio.h>

int str_len(char *s) {
    int n;

    for (n=0; *s!='\0'; n++, s++)   // se puede modificar directamente s porque es una copia local
        ;
    return n;
}

int str_len2(char *s) {
    char *p = s; // apunta a la misma dirección que s

    while (*p != '\0') {
        p++;
    }

    return p-s;
}

int main() {
    char str[] = "Hola mundo";

    printf("%d", str_len(str));
}