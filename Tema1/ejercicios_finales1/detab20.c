# include <stdio.h>

# define N 2
# define MAXLEN 100000

/* programa con funcion detab para sustituir tabulaciones por espacios */

void detab(void);
int getline(void);

char line[MAXLEN];

int main()
{   
    int len;

    while ((len = getline())>0){
        detab();
    }
}

int getline(void) 
{
    int c, i=0;
    extern char line[];

    while ((c=getchar())!=EOF && c!='\n' && i<MAXLEN-1) {
        line[i] = c;
        ++i;
    }
    
    if (c=='\n') {
        line[i] = c;
        ++i;
    }

    line[i] = '\0';

    return i;

}

void detab(void)
{
    extern char line[];
    int i = 0;
    int j;

    while (line[i]!='\0') {
        if (line[i] == '\t')
            for (j=1; j<=N; ++j)
                printf("e");
        else
            printf("%c", line[i]);
        ++i;
    } 
}
