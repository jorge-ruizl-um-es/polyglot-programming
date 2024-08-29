# include <stdio.h>
# define MAX 20000

// ejercicio para practicar la sentencia switch-case

// funcion escape(s,t) para convertir caracteres como nueva linea o tabulacion en sus secuencias de escape visibles
// tambien tiene que copiar la cadena s a t, inicialmente vacia

void escape(char s[], char t[]);
int getline(char s[]);
void rev_escape(char s[], char t[]);

void escape(char s[], char t[])
{
    int i, j;
    i = j = 0;

    while (s[i]!='\0') {
        switch(s[i]){
            case '\n':
                t[j++] = '\\';
                t[j++] = 'n';
                break;
            case '\t':
                t[j++] = '\\';
                t[j++] = 't';
                break;
            default:  
                t[j++] = s[i];
                break;
        }
    ++i;
    }

    t[j++] = '\n';
    t[j] = '\0';
}

int getline(char s[])
{
    int c, i;

    for (i=0; i < MAX -1 && (c = getchar()) != EOF && c!='\n'; ++i)
        s[i] = c;
    
    if (c=='\n')
        s[i++] = c;
    s[i]='\0';

    return i;
}

int main()
{
    int len;
    char s[MAX];
    char t[MAX];

    while ((len = getline(s)) > 0){
        escape(s, t);
        printf("%s", t);
    }
}