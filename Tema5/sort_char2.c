# include <stdio.h>
# include <string.h>

# define MAXLINES 5000  // máx. numero de lineas para ordenar
# define MAXLEN 1000    // máx longitud de una cadena de texto
# define BUFFSIZE 10000     // máx tamaño de almacenamiento de palabras total

char *lineptr[MAXLINES];    // array de punteros a cadenas (externo, común a todas las funciones)

/*
organización del array:

lineptr = [puntero a cadena 1, ..., puntero a cadena 5000 (como mucho)]
*/

int readlines(char *lineptr[], int); 
void writelines(char *lineptr[], int);

void qsort(char *lineptr[], int left, int right);

char total_lines[BUFFSIZE];

// ordenar lineas de entrada
int main() {
    int nlines;

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;   // ejecución correcta
    }
    else {
        printf("Error en la ordenacion: entrada demasiado grande\n");
        return 1;   // ejecución erronea
    }
}

int getline(char *, int);

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

// readlines lee lineas de entrada y las almacena en un buffer (funcion strcpy)
int readlines(char *lineptr[], int maxlines) {
    int len, nlines = 0;
    char line[MAXLEN], *p = total_lines;
    // inicializa p a la primera posicion de total_lines

    while ((len = getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || p+len >= total_lines+BUFFSIZE)
            return -1;
        else {
            line[len-1] = '\0';     // elimina fin de linea
            strcpy(p, line);    // copia en el espacio del array con todas las lineas la linea leida con getline 
            lineptr[nlines++] = p;  // almacena en la lista de lineas el puntero a la linea en el array
            p += len; // actualiza p a la siguiente posición libre de total_lines
        }
    }
    return nlines;
}

// escribir las lineas del array de cadenas (punteros)
void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

// algoritmo de ordenación quicksort con la función strcmp de string.h
void swap(char *v[], int i, int j) {
    char *temp;     // v[i] y v[j] son punteros a cadenas!!!

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void qsort(char *lineptr[], int left, int right) {
    int i, last;
    void swap(char *v[], int i, int j);

    if (left>=right)
        return;
    swap(lineptr, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (strcmp(lineptr[i], lineptr[left])<0)  // si la comparación es <0, es porque el de la izq tiene mayores valores ASCII (mayor orden alfabetico)
            swap(lineptr, ++last, i);
    swap(lineptr, left, last);
    qsort(lineptr, left, last-1);
    qsort(lineptr, last+1, right);
}