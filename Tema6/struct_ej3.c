# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <stdlib.h>

/*
Programa para llevar la cuenta de las lineas donde aparecen palabras de al menos 4 caracteres. Imprime el numero de linea en 
las que aparece cada una
*/

# define MAXWORD 100
# define MAXLINES 100

struct tnode {      // un nodo del árbol
    char *word;     // apunta hacia el texto (contenido del nodo)
    int lines[MAXLINES];      // cada line[i] para un nodo es una lista de las lineas donde aparece
    int *linep;         // puntero a la posición del array "lines" donde añadir un numero de linea
    struct tnode *left;     // apunta al hijo izquierdo del nodo
    struct tnode *right;    // apunta al hijo derecho
};

static int nline = 1;

// declaración de funciones:

struct tnode *addtree (struct tnode *, char *);
void treeprint (struct tnode *);
int getword(char *, int);

/* conteo de frecuencia de palabras */

int main() {
    struct tnode *root;     // puntero a un nodo que es la raíz del árbol
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) && strlen(word)>3)
            root = addtree(root, word);     
            /*
            En la primera llamada, root será hijo de NULL (será la raíz del arbol como tal). Se asigna el nodo root como el 
            primer nodo introducido y así se mantiene durante la ejecución.

            En las sucesivas llamadas, la función se llama a sí misma en la búsqueda binaria, modificando los right y left de los 
            nodos. Sin embargo, siempre acabará devolviendo la misma root al resolver las llamadas recursivas. 
            */
    treeprint(root);
    return 0;
}

struct tnode *talloc(void);     // obtener espacio de almacenamiento para nuevo nodo. Regresa puntero a espacio libre para almacenarlo
char *str_dup(char *);

struct tnode *addtree(struct tnode *p, char *w) {

    int cond;

    if (p == NULL) {    // palabra w no encontrada
        p = talloc();   // se crea un nuevo nodo
        p->word = str_dup(w);
        p->linep = p->lines;    // inicializo el puntero al array de indices de linea
        *(p->linep++) = nline;  // meto el indice de la linea leida y aumento el puntero
        *(p->linep) = -1;   // marca de fin de array
        p->left = p->right = NULL;      // no tiene hijos
    }
    else if ((cond = strcmp(w, p->word))==0) {
        *(p->linep++) = nline;
        *(p->linep) = -1;
    }
    else if (cond<0)     // usamos la variable cond para no repetir la operacion strcmp
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);
    return p;
}

// función talloc que hace uso de malloc para (stdlib) para localizar un espacio apropiado en memoria donde guardar
// una estructura nodo arbitraria. Devuelve la dirección de memoria donde guardarla.

struct tnode *talloc (void) {
    return (struct tnode *) malloc(sizeof(struct tnode));
    // convierte la salida de malloc (void) a un puntero a un nodo con un casting
}

// función strdup para copiar la cadena dada por su argumento a un lugar seguro obtenido por una llamada a malloc
// devuelve puntero al sitio donde se copia la cadena

char *str_dup (char *s) {
    char *p;

    p = (char *) malloc(strlen(s)+1);   // le sumamos uno por '\0'
    if (p != NULL)
        strcpy(p, s);
    return p;
}

// imprimir arbol

void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("Palabra \"%s\":\n", p->word);
        int *pointer = p->lines;
        while (*pointer != -1) {
            printf("\tLinea %d\n", *(pointer++));
        }
        treeprint(p->right);
    }
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

    while ((c = getch())==' ' || c == '\t')
        ;
    
    if (c != EOF)
        *w++ = c;
    if (c=='\n') {
        nline++;
        c = getch();
    }
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