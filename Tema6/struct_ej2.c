# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <stdlib.h>

# define MAXWORD 100
# define DEFAULT_PATTERN_LEN 6
# define NTYPES 6

static char *types[] = {"char", "double", "float", "int", "long", "short"};
// variables estaticas (externas) para que en cada llamada a getword permanezcan y puedan ser modificadas
static int comment_simple=0;
static int comment_double=0;
static int string=0;

struct tnode {      // un nodo del árbol
    char *word;     // apunta hacia el texto (contenido del nodo)
    struct tnode *left;     // apunta al hijo izquierdo del nodo
    struct tnode *right;    // apunta al hijo derecho
};

// lista enlazada
struct gnode {      // estructura para grupos de variables con el mismo prefijo
    char *pattern;
    int count;          // numero de elementos en un mismo grupo
    struct tnode *root;     // puntero a la raiz de un arbol binario que contiene cadenas que empiezan con el patron
    struct gnode *next;     // apunta al siguiente grupo
};

// declaración de funciones:

struct tnode *addtree (struct tnode *, char *);
struct gnode *addgroups (struct gnode *, char *, char *);
void treeprint (struct tnode *);
void groupprint (struct gnode *);
int getword(char *, int);
int binsearch(char *, char *[], int);

/* detección de nombres de variables con un mismo patrón */

int main(int argc, char *argv[]) {
    struct gnode *groups = NULL;
    int pattern_len = DEFAULT_PATTERN_LEN;
    char c;
    char word[MAXWORD];

    if (argc>1 && isdigit(c=(*++argv)[0])) {
        pattern_len = *argv - '0';
    }
    else if (argc>1 && !isdigit(c)) {
        printf("Error -- Uso: find_var (num)\n");
        return -1;
    }

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) && binsearch(word, types, NTYPES) >= 0) {
            char new_word[MAXWORD];
            if (getword(new_word, MAXWORD) != EOF) {
                char prefix[MAXWORD];
                strncpy(prefix, new_word, pattern_len); // construcción del prefijo con n caracteres
                prefix[pattern_len] = '\0';
                groups = addgroups(groups, prefix, new_word);
            }
        }
    groupprint(groups);
    return 0;
}

/* 
Función addtree: 
    Es una función a la que se llama recursivamente. Contiene una palabra que se busca en los nodos. 
    Si se encuentra un apuntador a NULL en el nodo, significa que ese nodo no existe y se crea, almacenando la palabra.
    Si la palabra se encuentra, incrementa su miembro count.
    Si no se encuentra, se busca en los nodos izquierdo o derecho según strcmp sea negativo o positivo respectivamente.
*/

struct tnode *talloc(void);     // obtener espacio de almacenamiento para nuevo nodo. Regresa puntero a espacio libre para almacenarlo
char *str_dup(char *);

struct tnode *addtree(struct tnode *p, char *w) {

    int cond;

    if (p == NULL) {    // palabra w no encontrada
        p = talloc();   // se crea un nuevo nodo
        p->word = str_dup(w);
        p->left = p->right = NULL;      // no tiene hijos
    }
    else if ((cond = strcmp(w, p->word))==0) {
        ;
    }
    else if (cond<0)    // usamos la variable cond para no repetir la operacion strcmp
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

struct gnode *galloc(void) {
    return (struct gnode *) malloc(sizeof(struct gnode));
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
        printf("%s\n", p->word);
        treeprint(p->right);
    }
}

// funciones de control de la estructura gnode

struct gnode *addgroups(struct gnode *g, char *prefix, char *w) {
    struct gnode *gp;

    for (gp=g; gp!=NULL; gp = gp->next) {
        if (strcmp(prefix, gp->pattern)==0) {
            gp->root = addtree(gp->root, w);     // se coloca word en el arbol ya existente dentro del grupo
            // el hecho de que cada grupo sea un árbol hace que addtree no haga nada si la palabra ya existe en el grupo (strcmp)
            // se ha modificado addtree para que no haga nada en caso de palabra coincidente
            gp->count++;
            return g;   // siempre se devuelve el primero en la lista enlazada (en este caso el que era antes el primero)
        }
    }

    // se crea un nuevo grupo añadiendo un árbol nuevo a root
    gp = galloc();
    gp->pattern = str_dup(prefix);  // guardar en memoria el prefijo
    gp->root = NULL;    // construir nuevo arbol (siempre que no se active el condicional del for en ninguna iteración, habrá que construir uno)
    gp->root = addtree(gp->root, w);    // asignación de la raíz desde NULL
    gp->next = g;   // se va poniendo g el último --> se añaden nodos por el principio (menos costoso)
    gp->count = 1;
    return gp;      // siempre se devuelve el primero en la lista enlazada (en este caso el que se crea)
}

// imprime los grupos con dos o más ocurrencias de palabras que compartan patrón
void groupprint(struct gnode *g) {
    struct gnode *gp;
    for (gp = g; gp!=NULL; gp = gp->next) {
        if (gp->count > 1) {    // esta es la utilidad del miembro count (imprimir solo grupos con más de un miembro)
            printf("Group: %s\n", gp->pattern);
            treeprint(gp->root);
            printf("\n");
        }
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

    while (string || comment_double || comment_simple) {
        // si se entra en este bucle, estará constantemente en él hasta que detecte la salida de comentario o cadena
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

// busqueda binaria
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