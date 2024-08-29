# include <stdio.h>
# include <ctype.h>
# include <string.h>

# define NTYPES 6       // tipos de datos
# define MAXWORD 100
# define MAXVARS 100    // maximo numero de nombres de variables que coinciden en el patron de inicio
# define MAXGROUPS 1000     // maximo numero de grupos que puede haber
# define MAXSIZE 6      // maximo tamaño a elegir del patron

static char *types[] = {"char", "double", "float", "int", "long", "short"};

struct variables {
    char *names[MAXVARS];
    int count;
    char *pattern;
};

int getword(char *, int);
int binsearch(char *, char *[], int);

static int comment_simple=0;
static int comment_double=0;
static int string=0;
static struct variables varlist[MAXGROUPS];

int main() {
    int nvar = 0;   // numero de grupos de variables
    char word[MAXWORD];

    while(getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) && binsearch(word, types, NTYPES) >= 0) {
            char new_word[MAXWORD];
            if (getword(new_word, MAXWORD) != EOF) {
                char patron[6];
                int i;
                for (i = 0; i < 6 && i < strlen(new_word); i++) {
                    patron[i]=new_word[i];
                }
                patron[i] = '\0';

                int found = 0;

                int j = 0;
                while (j < nvar && !found) {
                    if (strcmp(varlist[j].pattern, patron)==0) {
                        varlist[j].names[varlist[j].count] = new_word;
                        printf("%s\n", varlist[j].names[varlist[j].count]);
                        varlist[j].count++;
                        found = 1;
                    }
                    j++;
                }

                if (found==0) {
                    struct variables new_group;     // reservar espacio y esas cosas. esto no funciona porque trabajas siempre
                                                    // sobre la misma variable, no vas creando nuevos grupos
                    new_group.names[0] = new_word;
                    new_group.count = 1;
                    new_group.pattern = patron;
                    varlist[nvar++] = new_group;
                    printf("%s\n", varlist[nvar-1].names[varlist[nvar-1].count-1]);
                }

            }
        }
    }

    printf("%d\n",nvar);

    for (int k=0; k<nvar; k++) {
        if (varlist[k].count > 1) {
            int i = 0;
            while (i<varlist[k].count) {
                printf("%s  ", varlist[k].names[i]);
                i++;
            }
            printf("\n");
        }
    }

    return 0;
}

int binsearch(char *word, char *tab[], int n) {
    int cond;
    int low, high, mid;

    low = 0;
    high = n-1;
    while (low <= high) {
        mid = (low+high)/2;
        if ((cond = strcmp(word, tab[mid])) < 0)
            high = mid-1;
        else if (cond > 0)
            low = mid+1;
        else
            return mid;
    }
    return -1;
}

// funciones de lectura de palabras

int buffer[1000];
int *pbuf = buffer;

int getch(void) {
    return (pbuf > buffer) ? *(--pbuf) : getchar();
}

void ungetch(int c) {
    if (pbuf > buffer + 1000)
        printf("Error");
    else
        *pbuf++ = c;
}

int getword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (string || comment_double || comment_simple) {
        c = getch();
        if (c=='*') {
            char next;
            if ((next = getch()) == '/')
                comment_double  = 0;
            else
                ungetch(next);
        }
        else if (c=='"')
            string = 0;
        else if (c=='\n')
            comment_simple = 0;
    }

    while (isspace(c = getch())) {
        ;
    }

    if (c != EOF) {
        *w++ = c;
    }
    
    if (c == '/') {
        char next;
        if ((next=getch())=='*' && !comment_double) {
            comment_double = 1;
            *w = '\0';
            return c;
        }
        else if (next=='/' && !comment_simple) {
            comment_simple = 1;
            *w = '\0';
            return c;
        }
        else {
            ungetch(next);
        }
    }
    else if (c=='"' && !string) {
        string = 1;
        *w = '\0';
        return c;
    }
    else if (!isalpha(c) && c!='/' && c!='_' && c!='*' && c!='"') {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++)
        if (!isalnum((*w=getch())) && *w!='/' && *w!='_') {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}