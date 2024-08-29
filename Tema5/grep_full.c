# include <stdio.h>
# include <string.h>

# define MAXLINE 1000
# define MAXLINES 100
# define MAXLEN 1000000

int getline(char *line, int max);

/* find: imprime líneas que coinciden con el patrón del primer argumento 
Argumentos optativos:
    - x --> imprime todas las lineas excepto las que contengan el patron
    - n --> imprime delante de cada linea su numero
*/



int main (int argc, char *argv[]) {
    char line[MAXLINE];
    long lineno = 0;
    int c, except = 0, number = 0, found = 0;

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
    else
        while (getline(line, MAXLINE) > 0) {
            lineno++;   // primero se incrementa para usar notación "normal" (empezar la cuenta en 1)
            if ((strstr(line, *argv) != NULL) != except) {  // para el manejo de la opcion -x (si except es 1, se invierte)
                if (number) 
                    printf("%1d. ", lineno);
                printf("%s", line);
                found++;
            }
        }
    return found;
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