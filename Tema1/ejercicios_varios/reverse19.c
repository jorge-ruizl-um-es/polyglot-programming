# include <stdio.h>

# define MAXLEN 20000

/* programa con funcion reverse para invertir cadena s */

int getline(char line[], int limit);
void reverse(char s[]);

int main()
{
    char line[MAXLEN];
    int len;
    
    while ((len = getline(line, MAXLEN))>0) {
        reverse(line);
    }

}

int getline(char line[], int limit)
{
    int c, i = 0;

    while ((c=getchar())!=EOF && c!='\n' && i<limit-1) {
        line[i]=c;
        ++i;
    }

    if (c=='\n') {
        line[i] = c;
        ++i;
    }

    line[i] = '\0';

    return i;
}

void reverse(char s[])
{
    int i = 0;
    int j;

    while (s[i]!='\0')
        ++i;
    
    for (j=i-1; j>=0; --j) {
        printf("%c", s[j]);
    }
    printf("\n");
}