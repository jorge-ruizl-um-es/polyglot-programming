# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <stdlib.h>

/*
Representación de una tabla hash mediante una struct:
    Definimos struct nlist con forma de lista de nodos enlazados. Cada nodo tiene una referencia al siguiente, y referencias a cadenas
    que indican la palabra clave (name) y el texto de reemplazo (defn)

    La tabla será un array de listas enlazadas. La función hash devolverá un indice i para alojar el nodo correspondiente en
    hashtab[i]. Si se produce una colisión en el índice i, ambos nodos se alojarán en hashtab[i] en forma de lista enlazada,
    siendo el nodo más recientemente añadido el primero (se añade por delante).
*/

# define HASHSIZE 21   // tamaño de la tabla
# define KEYWORD "#define" 
# define KEYSIZE 7
# define MAXLINE 500

typedef struct nlist {
    struct nlist *next;     // referencia al siguiente nodo de la lista enlazada
    char *name;     // palabra guardada en el nodo
    char *defn;     // palabra que la sustituye
} Entrada;  // gracias a typedef, Entrada ahora equivale a crear una variable del tipo struct nlist

Entrada *hashtab[HASHSIZE];      // array a una tabla de punteros a nodos de los definidos como instancias de nlist
// Por tanto, cada posición hashtab[i] representa una lista enlazada

// función hash --> a partir de una cadena, saca un valor hash para indexar la tabla. Usamos unsigned para asegurar que el indice es 
// no negativo

unsigned hash(char *s) {
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31*hashval;
    return hashval % HASHSIZE;   // el operador % garantiza que el índice está entre 0 y HASHSIZE-1 para indexar correctamente
}

// función lookup --> llama a la función hash dada una palabra, y busca en la lista enlazada de la posición dada por hash

Entrada *lookup(char *s) {
    Entrada *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np -> next) {      // recorrer la lista enlazada
        if (strcmp(np->name, s) == 0)   // comparar con la cadena alojada
            return np;
    }
    return NULL;
}

// función install --> Usa lookup para buscar si ya existe la instancia en la tabla de un nodo con un nombre. Si está, cambia
// el valor defn por uno nuevo. Si no está, crea la instancia en la tabla. Devuelve puntero a la instancia creada o modificada,
// o NULL si no puede alojarse por temas de memoria

Entrada *install(char *name, char *defn) {

    Entrada *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {      // name no encontrado en ninguna entrada de hashtab
        np = (struct nlist *) malloc(sizeof(*np));  // aloja la struct nlist y devuelve el puntero a la estructura alojada
        if (np == NULL || (np -> name = strdup(name)) == NULL)  // se aloja el nombre en np->name
            return NULL;
        hashval = hash(name);
        
        // hashtab[hashval] apuntará inicialmente al primer elemento de la lista enlazada de esa posición en la tabla
        np -> next = hashtab[hashval];     // enlazamos el nodo introducido al principio de la lista de la posición
        hashtab[hashval] = np;          // hacemos que hashtab[hashval] apunte a él (primer elemento)
    }

    else {
        free((void *) np -> defn);  // libera la anterior defn
    }

    // pase lo que pase, se aloja defn en np->defn

    if ((np -> defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

// OJO! Se puede producir una colisión, es decir, distintos names que se guarden en el mismo indice
// Ante eso, se alojan ambos nodos en la misma entrada de la tabla, ampliando la lista enlazada de la posición 

void print_tab(Entrada *hashtab[]) {
   for (int i = 0; i < HASHSIZE; i++) {
        printf("Index %d: ", i);
        Entrada *current = hashtab[i];
        while (current != NULL) {
            printf("(%s, %s) -> ", current->name, current->defn);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// función undef para borrar un nombre y una definición de la tabla hash

void undef (char *name) {

    Entrada *np;
    unsigned hashval = hash(name);

    // buscamos con lookup
    if ((np = lookup(name))==NULL) {   // si no lo encuentra, no hay nada para borrar
        printf("Error: elemento no encontrado");
    }

    else {
        hashtab[hashval] = np->next;
        free((void *) np -> defn);
        free((void *) np -> name); 
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

    while ((c = getch()) == ' ' || c == '\t')
        ;
    
    if (c != EOF)
        *w++ = c;
    else
        return c;

    if (c == '\n')
        return c;

    for (; --lim > 0; w++)
        if (isspace(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}


# define MAXLEN 100

int main() {
    
    char word[MAXLEN];

    while (getword(word, MAXLEN) != EOF) {

        if (strcmp(word, KEYWORD) == 0) {
            char new_word[MAXLEN];
            int words = 0;
            char palabras[2][MAXLEN];

            while (getword(new_word, MAXLEN) != '\n' && new_word[0] != EOF) {
                if (words >= 2) {
                    printf("Error: define tiene que ir acompañado de 2 palabras");
                    return -1;
                }
                strcpy(palabras[words++], new_word);    // OJO CON ESTO --> no vale con =, hay que alojar la palabra en memoria
            }
            if (words != 2) {
                printf("Error: define tiene que ir acompañado de 2 palabras\n");
                return -1;
            }
            install(palabras[0], palabras[1]);
        }
    }
    print_tab(hashtab);
}

