# include <stdio.h>
# include <string.h>

# define MAXLINE 1000
# define MAXLINES 100
# define MAXLEN 1000000

int my_getline(char *line, int max);
void ltoa(long i, char *str);   // long to ASCII

/* find: imprime líneas que coinciden con el patrón del primer argumento 
Argumentos optativos:
    - x --> imprime todas las lineas excepto las que contengan el patron
    - n --> imprime delante de cada linea su numero
*/



int main (int argc, char *argv[]) {
    char line[MAXLINE];
    char *totlines[MAXLINES];   // array que almacena lineas
    char linebuf[MAXLEN];
    long lineno = 0;
    int c, except = 0, number = 0, found = 0, len;
    int nlines=0;   // contador de lineas con coincidencias
    char *p = linebuf;
    char **p2;
    char cadena[MAXLINE];
    char str_num[MAXLINE];  // para almacenar numeros en cadena

    while (--argc > 0 && (*++argv)[0]=='-') {   // estamos ante el caso de argumentos que empiecen por '-' (opciones)
        // estudiamos el primer elemento de la opcion (*++argv es el puntero a la cadena)
        while (c = *++argv[0] /* != '\0' */) {    // como [] tiene más prioridad que *; aquí estamos empezando por argv[0] (primera palabra de argv
        // actual tras el ciclo anterior). Lo incrementamos porque nos interesa a partir del segundo caracter, y desreferenciamos.
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default:    // ejecucion erronea
                    printf("find: opcion ilegal %c\n", c);
                    argc = 0;
                    found = -1;
                    break;
            }
        }
    }
    if (argc != 1)
        printf("Uso: find -x -n patron\n");
    else {
        while ((len = my_getline(line, MAXLINE)) > 0) {
            lineno++;   // primero se incrementa para usar notación "normal" (empezar la cuenta en 1)
            if ((strstr(line, *argv) != NULL) != except) {  // para el manejo de la opcion -x (si except es 1, se invierte)
                if (number) {
                    ltoa(lineno, str_num);
                    len += strlen(str_num);
                    strcpy(cadena, str_num);
                }
                strcat(cadena, line);
                if (nlines < MAXLINES && p+len < linebuf + MAXLEN) {
                    cadena[len-1] = '\0';
                    strcpy(p, cadena);
                    totlines[nlines++] = p;
                    p+=len;
                    found++;
                }
                else {
                    printf("Error");
                }
            }
        }

        for (p2 = totlines; p2 < totlines + nlines; p2++) {
            printf("%s\n", *p2);
        }

    return found;
    }
}

int my_getline(char *line, int max) {
    int i = 0, c;

    while ((c=getchar()) != EOF && c!='\n' && i<max-1)
        *(line+(i++)) = c;
    
    if (c=='\n')
        *(line+(i++)) = c;
    *(line+i) = '\0';
    return i;
}

void reverse(char *s) {
    int i, j, c;

    for (i=0, j=strlen(s)-1; i<j; i++,j--){
        c = s[i], s[i] = s[j], s[j] = c;
    }
}

void ltoa(long i, char *str) {  // i será entero positivo
    char *p = str;

    do {
        *p = i%10 + '0';
        p++;
    } while ((i/=10) > 0);
    *p = '\0';
    reverse(str);
    *p++ = ':';
    *p = '\0';
}