/* 
Extensión del programa de ordenamiento --> 
    Permite ordenar por orden alfabetico o el valor numerico de las cadenas introducidas (si son palabras, el numero es 0).

    OPCIONES:
        - Opción -n para indicar que se quiere ordenar un array numéricamente de menor a mayor
        - Opción -r para especificar que se quiere invertir el orden (de mayor a menor numéricamente o alfabético descendente)
        - Opción -f para no distinguir minusculas y mayusculas. Para implementarla, si se detecta, se compararán las palabras
        convirtiendolas a minuscula dentro de la función de ordenación.
        - Opción -d para tener en cuenta únicamente letras, dígitos y blancos en la ordenación (orden de directorio)

    Se podrán combinar a voluntad estas 4 opciones, aunque la combinación -nf, por ejemplo, no tendrá sentido.

    MEJORA - ORDENACIÓN POR CAMPOS:

        Ejemplo --> Nombre (SEP) Edad (SEP) Salario --> Ordenar cada columna según opciones independientes.

        USO: Hay que especificar las opciones de ordenación de cada campo de la siguiente manera:
            sort 1 (opts) 2 (opts) ... n (opts)

        IMPORTANTE: 
        Si no se quieren aplicar opciones sobre un campo, este puede omitirse, a no ser que sea el campo de mayor
        índice, en cuyo caso debe incluirse para especificar el número de campos a tener en cuenta. En el ejemplo, si no quisieramos 
        aplicar opciones extra a ningún campo, habría que poner: "sort n" si hemos introducido n campos.

        El carácter separador de campos será por defecto la tabulación. Si se quiere usar otra separación, se deberá modificar la 
        constante simbólica SEPARATION.
*/

# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <math.h>
# include <stdlib.h>

# define MAXLINES 100  // máx. numero de lineas para ordenar
# define MAXFIELDS 10   // máx. numero de campos
# define SEPARATION '\t'    // caracter separador de campos

// estructura para almacenar las opciones de cada campo (estarán en 1 las que se activen)
// definiremos un array del tipo FieldOptions para guardar las opciones del campo i

typedef struct {
    int numeric;
    int reversed;
    int minus;
    int direct;
} FieldOptions;

// declaración de funciones:

int parse_options(int, char *[], FieldOptions[], int *);
// esta función se encargará de detectar, para cada campo i, las opciones de ordenación; y además detectará el número total de campos
int split_line(char *line, char *fields[], int max_fields); 
// dada una linea de entrada, saca los campos y los guarda como palabras en un array de cadenas. Devuelve el numero de campos de la linea

int read_fields(char *lineptr[][MAXLINES], int, int); 
void write_fields(char *lineptr[][MAXLINES], int, int);

void q_sort(char *lineptr[], int left, int right, 
            int (*comp) (void *, void *), int f);   // funcion de ordenación

int numcmp(const char *, const char *);     // función para comparar dos cadenas que son numeros
void reverse(char *lineptr[], int);     // función para invertir el array de lineas (ya sea que contenga palabras o numeros)
void lower(char *);     // función para convertir una palabra a minusculas
int dircmp(const char *, const char *);     // función para comparar dos cadenas solo considerando letras, numeros y blancos


/* PROGRAMA PRINCIPAL */

// función para recuperar de los argumentos del programa los que se aplican a cada campo
// también sirve para determinar el número de campos (el usuario tendrá que espeficar el campo de mayor indice)

int parse_options(int argc, char *argv[], FieldOptions field_options[], int *num_fields) {  // pasar puntero para que pueda modificar la variable
    int field = -1;
    char c;

    while (--argc) {
        if (isdigit(c = (*++argv)[0])) {
            field = atoi(*argv);   // convertir el numero de campo a indice (campo 1 -> indice 0)
            if (field >= MAXFIELDS) {
                printf("Numero de campo demasiado grande\n");
                return -1;
            }
            if (*num_fields <= field)
                *num_fields = field + 1; // guarda el mayor campo para saber el número de campos
        }
        
        else if (c == '-') {
            if (field==-1) {    // error si detecta opción sobre campo no especificado
                printf("Error: campo indefinido");
                return -1;
            }

            while (c = *++argv[0]) {    // recorre el argumento que corresponda
                printf("%c\n", c);
                switch (c) {
                    case 'n':
                        field_options[field].numeric = 1;
                        break;
                    case 'r':
                        field_options[field].reversed = 1;
                        break;
                    case 'f':
                        field_options[field].minus = 1;
                        break;
                    case 'd':
                        field_options[field].direct = 1;
                        break;
                    default:
                        printf("sort: opcion ilegal %c\n", c);
                        return -1;
                }
            }
        }

        else {
            printf("Parametro no aceptado para la funcion: %c\n", c);
            return -1;
        }
    }
}


# define MAXLEN 1000    // máx longitud de una cadena de texto

// funciones auxiliares para readlines
int getline(char *, int);
char *alloc(int);

// lectura de una linea
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

/* 
Confiamos en que el usuario meterá siempre el mismo numero de campos
    
Mejora: si en una de las lineas que introduce, mete un número de campos distinto al especificado en la llamada al programa,
la función split_line se encarga de devolver el número de campos detectado. La función read_lines lo interceptará y comprobará
si es menor que el número de campos especificado para devolver el error en consecuencia.
*/
int split_line(char *line, char *fields[], int num_fields) {
    int nfields = 0;
    char *ps = line;
    char *end;

    while (*ps != '\0' && nfields < num_fields) {
        int i = 0;
        end = ps;
        while (*end != SEPARATION && *end != '\0') {
            end++;
        }

        if (*end == SEPARATION) {
            *end = '\0';
            fields[nfields++] = ps;
            ps = end + 1;   // reinicia desde el caracter siguiente al separador
        }
        else if (*end == '\0') {
            fields[nfields++] = ps;
            ps = end;   
            // *ps = '\0' -> fin del while
        }
    }
    // devuelve el número de campos leidos en una linea de entrada
    return nfields;     
}

# define BUFFSIZE 10000

static char allocbuf[BUFFSIZE];
static char *allocp = allocbuf;

// alojamiento de palabras en memoria. Se usará para almacenar cada palabra j de cada campo i
char *alloc(int n) {
    if (allocbuf + BUFFSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    }
    else
        return 0;
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

            if (word[f_len-1]=='\n') {  // quitamos saltos de linea (no convenientes para ordenar)
                word[f_len-1] = '\0';
                f_len--;
            }

            if ((p = alloc(f_len+1)) == NULL) {     // se reserva un espacio más para \0
                printf("Error al asignar memoria");
                return -1;
            }
            strcpy(p, word);
            lineptr[i][j] = p;  // puntero a la palabra almacenada
        }
        j++;
    }
    return j;
}

// escribir los distintos elementos de cada campo en una linea distinta
void write_fields(char *lineptr[][MAXLINES], int nlines, int num_fields) {
    for (int i = 0; i < num_fields; i++) {
        printf("Campo %2d: ", i+1);
        for (int j = 0; j < nlines; j++) {
            printf("%s  ", lineptr[i][j]);
        }
        printf("\n");
    }
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

// función para el orden de directorio
int dircmp(const char *s1, const char *s2) {
    do {
        // ignorar caracteres que no sean alfanumericos o espacios en AMBAS cadenas
        while (*s1 != '\0' && !isalnum(*s1) && !isspace(*s1))
            s1++;
        while (*s2 != '\0' && !isalnum(*s2) && !isspace(*s2))
            s2++;

        if (*s1 != *s2)
            return *s1 - *s2;
    } while (*s1++ && *s2++);
}

// función para invertir un array de palabras (punteros a cadenas)
void reverse(char *lineptr[], int nlines) {
    int i = 0, j = nlines-1;
    void *temp;

    while (i < j) {
        // lineptr[i] es un puntero a una cadena, por lo que temp no se desreferencia (queremos que temp también apunte a esa cadena)
        temp = lineptr[i]; 
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

// función para convertir a minúscula una palabra entera
void lower(char *s) {
    while (*s != '\0') {
        *s = tolower(*s);
        s++;
    }
}

// función para ordenar con el algoritmo quicksort
void q_sort(char *lineptr[], int left, int right, int (*comp) (void *, void *), int f) {
    int i, last;
    void swap(char *v[], int i, int j);

    if (left>=right)
        return;
    swap(lineptr, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; i++) {
        if (f) {
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
    q_sort(lineptr, left, last-1, comp, f);
    q_sort(lineptr, last+1, right, comp, f);
}

// Rutina main

int main(int argc, char *argv[]) {
    int nlines, num_fields = 0;
    FieldOptions field_options[MAXFIELDS] = {0};

    if (parse_options(argc, argv, field_options, &num_fields) == -1)
        printf("Uso: sort c1 opt1 ... cn (optn)\n");
        return 1;  // ejecución erronea en cuanto a la llamada al programa
    printf("%d\n", num_fields);  // depuración

    char *lineptr[MAXFIELDS][MAXLINES]; 
    // definimos un array de tantos arrays como campos haya, cada uno con tantas palabras como lineas se introduzcan

    if ((nlines = read_fields(lineptr, MAXLINES, num_fields)) >= 0) {
        for (int i = 0; i < num_fields; i++){
            q_sort((char **) lineptr[i], 0, nlines-1, (int (*) (void*, void*)) (field_options[i].numeric ? numcmp : (field_options[i].direct ? dircmp : strcmp)), field_options[i].minus);
            // la función q_sort recibe un puntero a una función de comparación para determinar cómo se ordena
            // esta función de comparación será una u otra dependiendo de las opciones activadas para dicho campo
        }
        write_fields(lineptr, nlines, num_fields);
        return 0;   // ejecución correcta
    }
    else {
        printf("Error en la ordenacion: entrada demasiado grande o numero insuficiente de campos\n");
        return 1;   // ejecución erronea en cuanto a la entrada introducida
    }
}
