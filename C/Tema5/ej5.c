# include <stdio.h>
# include <string.h>

// funcion strncpy(s, t, n) que copia n caracteres de t a s, regresando un puntero a s
// Rellena con \0  si t tiene menos de n caracteres

char *strn_cpy(char *s, char *t, int n) {
    int i;
    char *p;
    p = s;

    for (i=0; i<n && *t!='\0'; i++) {
        *s++ = *t++;
    }
    while (i++ < n) {
        *s++ = '\0';
    }
    *s = '\0';
    return p;
}

// funcion strncat(s, t, n) que hace lo mismo pero concatenando

char *strn_cat(char *s, char *t, int n) {
    int i = 0;
    char *p;
    p = s;

    while (*s != '\0')
        s++;
    while (i<n && *t != '\0') {
        *s++ = *t++;
        i++;
    }
    
    *s = '\0';
    return p;
}

int strn_cmp(char *s, char *t, int n) {
    // compara hasta n caracteres de ambas cadenas
    // devuelve 0 si son iguales, negativo si s<t o positivo si s>t

    int i;

    for (i=0; i<n; s++, t++, i++) {
        if (*s == '\0')
            return 0;
        else if (*s != *t)
            return *s-*t;
    }
    return 0;
}

int main() {
    char s[] = "Hola Mundo\n";
    char t[] = "\tAdios Mundo\n";    
    //printf("%s", strn_cpy(s, t, 10));
    //printf("%s", strn_cat(s, t, 10));
    printf("%d", strn_cmp(s, t, 10));
}
