# include <stdio.h>
# include <ctype.h>

# define MAXLEN 1000

/* funcion getint para, dada una linea, leer entero a entero, e ir metiendolos en el array, asignandolo a la posicion de este
pasada a la función como un puntero a dicha posición. 
Devuelve una señal '0' si no lee un entero; o el entero en sí */

char line[MAXLEN];
char *linep;

int main() {
    int n ,i, array[100], getint(int *pa), getline(char []), out;

    n = 0;
    while (getline(line)>0) {
        linep = line;
        while (n<100 && (out = getint(&array[n])) != '\0') {    // a getint se le pasa la dirección de memoria
            if (out==0) 
                ;
            else {
                n++;
            }
        }
    }

    for (i=0; i<n; i++)
        printf("%d ", array[i]);
    return 0;
}

int getline(char s[]) {
    int i, c;

    for (i = 0; i<MAXLEN-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

int getint(int *pa) {
    int c, sign;

    while (isspace(c = *linep++))
        ;

    if (!isdigit(c) && c!=EOF && c!='+' && c!='-') {
        return 0;
    }
    sign = (c == '-')? -1: 1;
    if (c=='+' || c=='-') {
        c = *linep++;
        if (!isdigit(c))    // ej 1
            return 0;
    }
    for (*pa=0; isdigit(c); c = *linep++) {
        *pa = 10*(*pa) + (c-'0');
    }
    *pa *= sign;

    return c;    // devolvemos el caracter para que pueda devolver EOF
}
