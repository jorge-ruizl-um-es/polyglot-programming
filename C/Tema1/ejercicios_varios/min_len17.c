# include <stdio.h>

/* programa que imprime todas las lineas de entrada de longitud mayor de MINLEN */

# define MAXLEN 10000
# define MINLEN 10

int getline(char line[], int lim);

int main()
{
    int len;
    char line[MAXLEN];

    while ((len = getline(line, MAXLEN))>0){
        if (len>MINLEN)
            printf("%s", line);
    }

}

int getline(char line[], int lim)
{
    int c, i;

    for (i=0; i<lim-1 && ((c=getchar()) != EOF) && c != '\n'; ++i)
        line[i]=c;
    
    if (c=='\n'){
        line[i]=c;
        ++i;
    }
    line[i]='\0';

    return i;
}