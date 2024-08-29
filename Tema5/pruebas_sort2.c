# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <math.h>

# define MAXLINES 5000  // máx. numero de lineas para ordenar
# define MAXFIELDS 10   // máx. numero de campos 

# define MAXLEN 1000    // máx longitud de una cadena de texto


typedef struct {
    int numeric;
    int reversed;
    int minus;
    int direct;
} FieldOptions;

int parse_options(int, char *[], FieldOptions[], int *);
// esta función se encargará de detectar, para cada campo i, las opciones de ordenación; y además detectará el número total de campos
int split_line(char *line, char *fields[], int max_fields); 
// dada una linea de entrada, saca los campos y los guarda como palabras en un array de cadenas. Devuelve el numero de campos de la linea

int read_fields(char *lineptr[][MAXLINES], int, int); 
void write_fields(char *lineptr[][MAXLINES], int, int);

void qsort(char *lineptr[], int left, int right, 
            int (*comp) (void *, void *), int f);

int numcmp(const char *, const char *);     // función para comparar dos cadenas que son numeros
void reverse(char *lineptr[], int);     // función para invertir el array de lineas (ya sea que contenga palabras o numeros)
void lower(char *);     // función para convertir una palabra a minusculas
int dircmp(const char *, const char *);     // función para comparar dos cadenas solo considerando letras, numeros y blancos


// programa principal

int parse_options(int argc, char *argv[], FieldOptions field_options[], int *num_fields) {
    int field = -1;
    char c;

    while (--argc) {
        if (isdigit(c = (*++argv)[0])) {
            field = c - '0' - 1;   // convertir el numero de campo a indice (campo 1 -> indice 0)
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
    }
}

