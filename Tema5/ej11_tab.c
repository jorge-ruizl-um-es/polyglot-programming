# include <stdio.h>
# include <string.h>

# define N 3
# define MAXLEN 1000

int getline(char *line, int max) {
    int i = 0, c;

    while (i<max-1 && (c=getchar()) != EOF && c!='\n')
        *(line+(i++)) = c;
    
    if (c=='\n')
        *(line+(i++)) = c;
    *(line+i) = '\0';
    return i;
}

void detab(char *line) {
    int i = 0;
    int j;

    while (line[i]!='\0') {
        if (line[i] == '\t')
            printf("  ");
        else
            printf("%c", line[i]);
        ++i;
    } 
}

int main(int argc, char *argv[]) {
    char line[MAXLEN];
    int len;
    int found;
    
    while ((len = getline(line, MAXLEN)) > 0) {
        if (argc==1) {
            detab(line);
        }
        else {
            for (int i = 0; i < len; i++) {     // recorremos la linea introducida
                found = 0;
                char **p = argv+1;  // puntero a la primera letra del primer argumento

                while (p < argv + argc && found==0) {   // recorremos argumentos desde el principio
                    char word = **p;
                    if (word=='\\') {
                        char space = *(*p+1);   // OJO!!! Los corchetes tienen más prioridad
                        // explicación: *p es un puntero a una cadena (posición inicial). Cogemos *p, le sumamos 1 para la siguient
                        // posición, y desreferenciamos para sacar la letra de dicha posición
                        switch (space) {
                            case 'n':
                                word = '\n';
                                break;
                            case 't':
                                word = '\t';
                                break;
                            default:
                                printf("Separador no valido\n");
                                return -1;
                        }
                    }
                    if (word == line[i]) {  // word es el caracter que habría que sustituir (tabulación)
                        for (int j = 0; j < N; j++)
                            printf(" ");
                        found = 1;
                    }
                    p++;
                }
                if (found==0) 
                    printf("%c", line[i]);
            }
        }
    }
}