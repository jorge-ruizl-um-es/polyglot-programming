/* 
Extensión del programa de ordenamiento --> 
    Permite ordenar por orden alfabetico o el valor numerico de las cadenas introducidas (si son palabras, el numero es 0). 
    Se indicará que se quiere ordenar numéricamente mediante la opción -n 

    Añado la opción -f para no distinguir minusculas y mayusculas. Para implementarla, si se detecta, se compararán las palabras
    convirtiendolas a minuscula dentro de la función de ordenación.

    Añado la opción -d para ignorar todo lo que no sean espacios, letras y numeros.
*/

# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <math.h>

# define MAXLINES 5000  // máx. numero de lineas para ordenar

char *lineptr[MAXLINES];    // array de punteros a cadenas (externo, común a todas las funciones)

/*
organización del array:

lineptr = [puntero a cadena 1, ..., puntero a cadena 5000 (como mucho)]
*/

int readlines(char *lineptr[], int); 
void writelines(char *lineptr[], int);

void qsort(char *lineptr[], int left, int right, 
            int (*comp) (void *, void *), int f);      // se le pasa un puntero a la funcion apropiada

int numcmp(const char *, const char *);     // función para comparar dos cadenas que son numeros
void reverse(char *lineptr[], int);     // función para invertir el array de lineas (ya sea que contenga palabras o numeros)
void lower(char *);     // función para convertir una palabra a minusculas
int dircmp(const char *, const char *);     // función para comparar dos cadenas solo considerando letras, numeros y blancos


// ordenar lineas de entrada
int main(int argc, char *argv[]) {
    int nlines;
    int numeric = 0, reversed = 0, minus = 0, direct = 0;
    char c;

    while (--argc > 0 && (*++argv)[0]=='-') {   // manejo de argumentos
        while (c = *++argv[0]) {
            switch (c) {
                case 'n':
                    numeric = 1;
                    break;
                case 'r':
                    reversed = 1;
                    break;
                case 'f':
                    minus = 1;
                    break;
                case 'd':
                    direct = 1;
                    break;
                default:
                    printf("sort: opcion ilegal %c\n", c);
                    argc = 0;
                    break;
            }
        }
    }

    if (argc != 0)
        printf("Uso: sort -r -n -f -d\n");
    else if (minus && numeric)
        printf("No tiene sentido usar las opciones 'n' y 'f' a la vez\n");
    else {
        if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
            qsort((char **) lineptr, 0, nlines-1, (int (*) (void*, void*)) (numeric ? numcmp : (direct ? dircmp : strcmp)), minus);
            // otra opcion: si numeric, entonces usar numcmp; si no, comprobamos si minus. Si minus, entonces usamos una funcion de
            // comparación que compare las minusculas (habría que programarla); si no, usamos strcmp
            if (reversed)
                reverse(lineptr, nlines);
            writelines(lineptr, nlines);
            return 0;   // ejecución correcta
        }
        else {
            printf("Error en la ordenacion: entrada demasiado grande\n");
            return 1;   // ejecución erronea
        }
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
        return allocp - n;
    }
    else
        return 0;
}

// readlines lee lineas de entrada y las almacena en un buffer (funcion strcpy)
int readlines(char *lineptr[], int maxlines) {
    int len, nlines = 0;
    char *p, line[MAXLEN];

    while ((len = getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len-1] = '\0';     // elimina salto de línea
            strcpy(p, line);    // copia en el espacio del buffer reservado con alloc (puntero p) la linea 
            lineptr[nlines++] = p;  // almacena en la lista de lineas el puntero a la linea
        }
    }
    return nlines;
}

// escribir las lineas del array de cadenas (punteros)
void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

// funcion para comparar numeros representados por cadenas
int numcmp(const char *s1, const char *s2) {
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);

    if (v1 < v2)
        return -1;  // negativo si es menor
    else if (v1 > v2) 
        return 1;
    else
        return 0;
}

int dircmp(const char *s1, const char *s2) {
    while (*s1++ && *s2++) {
        // ignorar todo lo que no sean blancos, letras y números de ambas cadenas
        while (*s1 != '\0' && !isalnum(*s1) && !isspace(*s1))
            s1++;
        while (*s2 != '\0' && !isalnum(*s2) && !isspace(*s2))
            s2++;
        if (*s1 != *s2)
            return *s1-*s2;
   }
   return 0;
}

// función para invertir un array de palabras (punteros a cadenas)
void reverse(char *lineptr[], int nlines) {
    int i = 0, j = nlines-1;
    char *temp;

    while (i < j) {
        temp = lineptr[i];  // lineptr[i] es un puntero a una cadena, por lo que temp no se desreferencia (queremos que temp también apunte a esa cadena)
        lineptr[i] = lineptr[j];
        lineptr[j] = temp;
        i++, j--;
    }

}

// algoritmo de ordenación quicksort con la función strcmp de string.h
void swap(char *v[], int i, int j) {
    void *temp;     // v[i] y v[j] son punteros a cadenas!!!

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void lower(char *s) {
    while (*s != '\0') {
        *s = tolower(*s);
        s++;
    }
}

// podria hacerse de otra forma pasandole como argumento el valor numeric y con un if-else (si es 
// numeric usa esta función, si no lo es usa esta otra)
void qsort(char *lineptr[], int left, int right, int (*comp) (void *, void *), int f) {
    int i, last;
    void swap(char *v[], int i, int j);

    if (left>=right)
        return;
    swap(lineptr, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; i++) {
        if (f) {    // igualar mayusculas y minusculas
            // necesitamos variables temporales porque si modificamos las palabras de entrada la recursividad ya no va
            char temp1[MAXLEN], temp2[MAXLEN];
            strcpy(temp1, lineptr[i]);
            strcpy(temp2, lineptr[left]);
            lower(temp1);
            lower(temp2);
            if ((*comp)(temp1, temp2) < 0)
                swap(lineptr, ++last, i);
        }
        else {
            if ((*comp)(lineptr[i], lineptr[left]) < 0) 
                swap(lineptr, ++last, i);
        }
    }
    swap(lineptr, left, last);
    qsort(lineptr, left, last-1, comp, f);
    qsort(lineptr, last+1, right, comp, f);
}

// Otra forma más eficiente de hacerlo???