# include <stdio.h>
# define MAXLEN 20000

/* programa que elimina espacios y tabulaciones al final de cada linea, y borra lineas en blanco*/

int getline(char line[], int maxlen);
int cleanline(char line[]);
void print_with_tabs(char line[], int len);
int copy_at_some_point(char base[], char in[], int index);

int main()
{
    char line[MAXLEN];
    char full_text[MAXLEN]="";
    int len, new_len, i;

    i=0;

    while ((len=getline(line, MAXLEN)) > 0) {
        new_len=cleanline(line);
        if (new_len>0)
            i = copy_at_some_point(full_text, line, i);
        /* para depuracion */
        /*
        if (line[0] != '\0') {
            print_with_tabs(line, new_len);
        }
        */
    }

    printf("%s", full_text);
    return 0;

}

int copy_at_some_point(char base[], char in[], int index)
{
    int i = 0;

    // el parametro index no es necesario ya que se puede calcular en la propia funcion con un while
    
    while ((base[index+i] = in[i]) != '\0')
        ++i;

    base[index+i]='\n';     // la funcion cleanline da la linea sin salto al final
    base[index+i+1]='\0';

    return index+i+1;
}


int getline(char line[], int maxlen)
{
    int i, c;

    for (i=0; (c=getchar())!=EOF && c!='\n' && i<maxlen-1; ++i) {
        line[i]=c;
    }
    if (c=='\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return i;
}

/* función para eliminar los espacios y tabuladores al final de la línea */
int cleanline(char s[]) {
    int i, j;

    i = 0;

    /* Encuentra el final de la cadena */
    while (s[i] != '\0') {
        i++;
    }

    /* Retrocede eliminando espacios y tabuladores */
    i--;
    while (i >= 0 && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')) {
        i--;
    }

    /* Coloca el carácter nulo en la nueva posición final */
    s[i+1]='\0';
    return i+1;
}

/* función para depurar */
void print_with_tabs(char line[], int len) {
    int i;

    for (i = 0; i < len; ++i) {
        if (line[i] == '\t')
            printf("t");
        else if (line[i] == ' ')
            printf("e");
        else
            printf("%c", line[i]);
    }
    printf("\n");
}