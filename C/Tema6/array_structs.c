# include <stdio.h>
# include <ctype.h>
# include <string.h>

# define NKEYS (sizeof keytab / sizeof(struct key))
// otra opción:
# define NKEYS2 (sizeof keytab / sizeof keytab[0])  // tamaño de todo entre tamaño de 1 elemento
# define MAXWORD 100

// definición del array de keys (estructura declarada) "keytab". 
// Cada posición keytab[i] representará la palabra clave i (word) junto
// con las veces que aparece (count)
// Es un poco como un diccionario de la forma {palabra_clave : veces_que_aparece}
struct key {
    char *word;     // esto no se va a modificar
    int count;
} keytab[] = {
    {"auto", 0},    // las llaves internas son bastante aclarativas, pero innecesarias... 
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"define", 0},
    /* ... */
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0}
};
// tmb podría declararse la estructura y luego definir el array

int getword(char *, int);
int binsearch(char *, struct key *, int);

int main() {
    int n;
    char word[MAXWORD];

    while(getword(word, MAXWORD) != EOF) {
        printf("%s\n", word);
        if (isalpha(word[0]))
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)  // si no encuentra word en keytab return -1
                keytab[n].count++;      // la n se usa!!!
    }
        
    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
    
    return 0;
}

int binsearch(char *word, struct key tab[], int n) {
    int cond;
    int low, high, mid;

    low = 0;
    high = n-1;
    while (low <= high) {
        mid = (low+high)/2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
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

    while (isspace(c = getch()))
        ;
    
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c) && c!='#' && c!='/' && c!='_') {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++)
        if (!isalnum(*w = getch()) && *w!='#' && *w!='/' && *w!='_') {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}