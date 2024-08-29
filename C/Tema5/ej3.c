# include <stdio.h>

// funcion que ccopia la cadena t al final de s CON PUNTEROS

void str_cat(char *s, char *t) {
    while (*s!='\0')
        s++;
    
    while ((*s++=*t++)!='\0')
        ;
}

int main() {
    char s[] = "Peste pestosa\n";   // s tiene que definirse como array porque se modifica
    char *t = "Peos pestosos";      // t no hace falta
    str_cat(s, t);
    printf("%s", s);
}