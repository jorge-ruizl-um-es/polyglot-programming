# include <stdio.h>
# define MAXLEN 20000

/* 
programa que simula el comportamiento de la función 'grep' de UNIX 
dada una entrada de n lineas, imprime las lineas que contengan la palabra s
*/

int getline(char s[]);  // va leyendo lineas
void concat(char input[], char output[]);   // va metiendo las lineas en una base de datos
int strindex(char s[], char t[]);   // devuelve la posicion de s donde empieza la cadena t, o -1 si no la contiene

// definicion de funciones

int getline(char s[])
{
    int i, c;

    for (i = 0; i<MAXLEN-1 && (c = getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    
    if (c == '\n')
        s[i++] = '\n';
    s[i] = '\0';
    return i;
}

void concat(char input[], char output[])
{
    int i=0, j=0;

    while (output[i]!='\0')
        ++i;
    
    while ((output[i++]=input[j++])!='\0')
        ;
    output[i] = '\0';
}

int strindex(char s[], char t[])
{
    int i, j, k;

    for (i=0; s[i]!='\0'; ++i){
        for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; ++j, ++k)
            ;
        if (k>0 && t[k]=='\0')
            return i;
    }
    return -1;
}


int main()
{
    char s[MAXLEN];
    char total[MAXLEN];
    int len;
    char busqueda[] = "texto prueba";

    while ((len=getline(s))>0)
        if (strindex(s, busqueda)>=0)
            concat(s, total);
    printf("%s", total);
}