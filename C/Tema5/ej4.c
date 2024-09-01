# include <stdio.h>
# include <string.h>

// funcion que regresa 1 si la cadena t está al final de s, 0 si no

int strend(char *s, char *t) {

    s += (strlen(s) - strlen(t));   // vamos a la posición de s en la que debe empezar t 
    if (s<0)
        return 0;   // si s queda negativa es porque t es más larga, s no puede contener a t al final
    while (*s!='\0' && *t!='\0') {
        if (*s++!=*t++)
            return 0;
    }
    
    return (*t == '\0');
}

int main() {
    char *s = "Hola mundo\n";   
    char *t = "mundos\n";    
    printf("%d", strend(s, t));
}
