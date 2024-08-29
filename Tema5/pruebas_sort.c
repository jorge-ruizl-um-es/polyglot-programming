# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <math.h>

# define MAXLINES 5000  // máx. numero de lineas para ordenar
# define MAXFIELDS 10   // máx. numero de campos 

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

// confiamos en que el usuario meterá siempre el mismo numero de campos
int split_line(char *line, char *fields[], int num_fields) {
    int nfields = 0;
    char *ps = line;
    char *end;

    while (*ps != '\0' && nfields < num_fields) {
        int i = 0;
        end = ps;
        while (*end != '\t' && *end != '\0') {
            end++;
        }

        if (*end == '\t') {
            *end = '\0';
            fields[nfields++] = ps;
            printf("%s\n", ps);
            ps = end + 1;
        }
        else if (*end == '\0') {
            fields[nfields++] = ps;
            printf("%s", ps);
            ps = end;   // *ps = '\0' -> fin del while
        }
    }
    return nfields;
}

// readlines lee lineas de entrada, las separa por campos y, por cada linea, guarda la información del campo i en el array de la posición 
// i del array multidimensional
int read_fields(char *lineptr[][MAXLINES], int maxlines, int num_fields) {
    int len, f_len;
    char *p, line[MAXLEN];
    int j = 0;

    while (j < maxlines && (len = getline(line, MAXLEN)) > 0) {
        char *fields[num_fields];

        if (split_line(line, fields, num_fields) != num_fields)
            return -1;
        for (int i = 0; i < num_fields; i++) {
            char *word = fields[i];
            f_len = strlen(word);

            if (word[f_len-1]=='\n') {
                word[f_len-1] = '\0';
                f_len--;
            }

            if ((p = alloc(f_len+1)) == NULL) {
                printf("Error al asignar memoria");
                return -1;
            }
            strcpy(p, word);
            lineptr[i][j] = p;
        }
        j++;
    }
    return j;
}

int main(int argc, char *argv[]) {
    int nlines;
    int num_fields = 3;


    char *lineptr[num_fields][MAXLINES]; 
    // definimos un array de tantos arrays como campos haya, cada uno con tantas palabras como lineas se introduzcan

    if ((nlines = read_fields(lineptr, MAXLINES, num_fields)) >= 0) {
        for (int i = 0; i < num_fields; i++) {
            printf("%s\n", *lineptr[i]);
            for (int j = 0; j < nlines; j++) {
                printf("%s ", lineptr[i][j]);
            }
            printf("\n");
        }
        return 0;   // ejecución correcta
    }
    else {
        printf("Error en la ordenacion: entrada demasiado grande o numero insuficiente de campos\n");
        return 1;   // ejecución erronea en cuanto a lineas
    }
}