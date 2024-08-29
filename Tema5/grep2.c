# include <stdio.h>
# include <string.h>

# define MAXLINE 1000
# define MAXLINES 100
# define MAXLEN 1000000

int getline(char *line, int max);

/* find: imprime líneas que coinciden con el patrón del primer argumento */

int main (int argc, char *argv[]) {
    char line[MAXLINE];
    char *totlines[MAXLINES];
    char linebuf[MAXLEN];
    int found = 0, len, nlines=0;
    char *p = linebuf;
    char **p2;  // puntero a array de cadenas

    if (argc != 2)
        printf("Uso: find patron\n");
    else {
        while ((len = getline(line, MAXLINE)) > 0)
            if (strstr(line, argv[1]) != NULL) {
                // strstr devuelve un puntero a la primera ocurrencia de t en s, o NULL si no hay ocurrencia
                if (nlines < MAXLINES && p+len < linebuf + MAXLEN) {
                    line[len-1] = '\0';
                    strcpy(p, line);
                    totlines[nlines++] = p;
                    p+=len;
                    found++;
                }
                else 
                    printf("Error");
            }
        for (p2 = totlines; p2 < totlines + nlines; p2++)
            printf("%s\n", *p2);    // puntero a cadena
    return found;
    }
    return 0;
}

int getline(char *line, int max) {
    int i = 0, c;

    while ((c=getchar()) != EOF && c!='\n')
        *(line+(i++)) = c;
    
    if (c=='\n')
        *(line+(i++)) = c;
    *(line+i) = '\0';
    return i;
}