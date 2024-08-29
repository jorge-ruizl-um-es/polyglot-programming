#include <stdio.h>
#include <ctype.h>  // Para tolower

void lower_all(char *s[], int nlines) {
    for (int i = 0; i < nlines; i++) {
        char *word = s[i];
        while (*word != '\0') {
            *word = tolower(*word);
            word++;
        }
    }
}

// Ejemplo de uso
int main() {
    // Asegurarse de que las cadenas son modificables
    char line1[] = "Hello";
    char line2[] = "WORLD";
    char line3[] = "TeSt";

    char *lines[] = {line1, line2, line3};
    int nlines = 3;

    lower_all(lines, nlines);

    for (int i = 0; i < nlines; i++) {
        printf("%s\n", lines[i]);
    }

    return 0;
}

