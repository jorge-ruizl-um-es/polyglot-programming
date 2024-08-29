# include <stdio.h>

// funcion que devuelve 0 si s y t son iguales, negativo si s es menor en su ASCII, y positivo si es mayor
int strcmp(char *s, char *t) {      // con punteros
    for ( ; *s==*t; s++, t++) {
        printf("%c", *s);
        if (*s == '\0') // si son iguales devolver 0
            return 0;
    }
    return *s-*t;   // si son distintas devolver negativo si s es más corta, y positivo si es más larga
}

int strcmp2(char *s, char *t) {     // con arrays
    int i;

    for (i=0; s[i] == t[i]; i++) {
        if (s[i]=='\0')
            return 0;
    }
    return s[i]-t[i];
}

int main() {
    char s[]= "Hola mundo";
    char t[] = "Peste pestosa";

    printf("%d", strcmp(s, t));
}