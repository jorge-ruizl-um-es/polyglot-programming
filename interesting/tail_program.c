# include <stdio.h>
# include <ctype.h>
# include <string.h>

# define MAXLINES 1000

char *todas_lineas[MAXLINES];

int readlines(char *[], int);
void tail(char *[], int, int);

int main(int argc, char *argv[]) {
    int n = -1, nlines;
    char c;

    if (argc>2 || (c=(*++argv)[0])!='-') {
        printf("Uso: tail -n. Se acepta uno o ningun argumento\n");
        return -1;
    }
     
    while (--argc && (c =='-')) {     // primera letra del segundo argumento
        c = *++argv[0]; // segunda letra del segundo argumento, que ahora es el primero
        if (isdigit(c))
            n = 0;
        while (isdigit(c)) {
            n = 10*n + (c-'0');
            c = *++argv[0];
        }
    }

    if (n==-1) {
        n = 10; // por omisión
    }

    if ((nlines = readlines(todas_lineas, MAXLINES)) >= 0) {    // readlines puede devolver -1 en caso de error
        tail(todas_lineas, n, nlines);
        return 0;   // ejecución correcta
    }
    else {
        printf("Error en la ordenacion: entrada demasiado grande\n");
        return 1;   // ejecución erronea
    }
}

# define MAXLEN 1000    // máx longitud de una cadena de texto

// funciones auxiliares para readlines
int getline(char *, int);
char *alloc(int);

int getline(char *s, int maxlen) {
    int c, i=0;

    while (i < maxlen-1 && (c = getchar())!=EOF && c!='\n') {
        *(s+i) = c;
        i++;
    }

    if (c=='\n') 
        *(s+(i++)) = c;
    *(s+i) = '\0';
    return i;
}

# define BUFFSIZE 10000

static char allocbuf[BUFFSIZE];
static char *allocp = allocbuf;

char *alloc(int n) {
    if (allocbuf + BUFFSIZE - allocp >= n) {
        allocp += n;
        return allocp-n;
    }
    else {
        return 0;
    }
}

int readlines(char *todas_lineas[], int maxlines) {
    int len, nlines=0;
    char line[MAXLEN];
    char *p;

    while ((len = getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len-1] = '\0'; 
            strcpy(p, line);
            todas_lineas[nlines++] = p;  // p ya es incrementado al llamar a alloc
        }
    }
    return nlines;
}

// funcion tail para imprimir las ultimas n lineas

void tail (char *todas_lineas[], int n, int nlines) {
    if (n>nlines)
        n = nlines;

    int i = nlines-n;

    while (i < nlines)
        printf("%s\n", todas_lineas[i++]);
}