# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <stdlib.h>

# define MAXWORD 100

/*
Programa para imprimir las palabras leidas como entrada de mayor a menor numero de aparición
*/

struct tnode {      // un nodo del árbol
    char *word;     // apunta hacia el texto (contenido del nodo)
    int count;      // número de ocurrencias de word
    struct tnode *left;     // apunta al hijo izquierdo del nodo
    struct tnode *right;    // apunta al hijo derecho
};

// declaración de funciones:

struct tnode *addtree (struct tnode *, char *);
int getword(char *, int);

// Funciones para ordenar palabras por frecuencia
void q_sort(struct tnode **, int, int);
void reverse(struct tnode **, int);
void tree_to_array(struct tnode *, struct tnode **, int *);
void print_treearray(struct tnode **, int);

/* conteo de frecuencia de palabras */

int main() {
    struct tnode *root;     // puntero a un nodo que es la raíz del árbol
    char word[MAXWORD];
    struct tnode **array;
    int n = 0;

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);     
            /*
            En la primera llamada, root será hijo de NULL (será la raíz del arbol como tal). Se asigna el nodo root como el 
            primer nodo introducido y así se mantiene durante la ejecución.

            En las sucesivas llamadas, la función se llama a sí misma en la búsqueda binaria, modificando los right y left de los 
            nodos. Sin embargo, siempre acabará devolviendo la misma root al resolver las llamadas recursivas. 
            */
    tree_to_array(root, array, &n);
    q_sort(array, 0, n-1);
    reverse(array, n);
    print_treearray(array, n);
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
        p->count = 1;   // registra primera aparición de w
        p->left = p->right = NULL;      // no tiene hijos
    }
    else if ((cond = strcmp(w, p->word))==0) {
        p->count++;
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

// Funciones de ordenación

// Convertir árbol a array de nodos. Se necesita pasar punteros para que modifiquen los valores de los parámetros
// en las sucesivas llamadas recursivas. Se pasa un puntero a un array de punteros a nodos.
void tree_to_array(struct tnode *root, struct tnode **array, int *n) { 
    if (root!=NULL) {
        // convertirlo en recorrido enorden (arbol binario)
        tree_to_array(root->left, array, n);    // root->left es puntero al hijo izquierdo de root
        array[(*n)++] = root;
        tree_to_array(root->right, array, n);
    }
}

void q_sort(struct tnode **array, int left, int right) {
    int i, last;
    void swap(struct tnode **v, int a, int b);

    if (left >= right)
        return;
    swap(array, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; i++) {
        // array[i] es un puntero a la posición i del array, que apunta a una struct node. se desreferencia accediendo a uno de sus miembros
        if (array[i]->count < array[left]->count)       // ordenar por count (aparicion)
            swap(array, ++last, i); 
    }
    swap(array, last, left);
    q_sort(array, left, last-1);
    q_sort(array, last+1, right);
}

void swap(struct tnode **v, int a, int b) {
    struct tnode *temp;

    temp = v[a];
    v[a] = v[b];
    v[b] = temp;
}

void reverse(struct tnode **v, int n) {
    int inicio = 0;
    int fin = n-1;
    while (inicio < fin) {
        swap(v, inicio++, fin--);
    }
}

void print_treearray(struct tnode **array, int n) {
    while(n--) {
        printf("%4d %s\n", (*array)->count, (*array)->word);
        array++;
    }
}