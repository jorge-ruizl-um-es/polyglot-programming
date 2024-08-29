# include <stdio.h>

# define MAX_LEN 1000
# define EMPTY -1
# define FULL (MAX_LEN - 1)

// pila de caracteres (NO DE CADENAS)

// Definicion de la estructura abstracta
typedef struct stack {
    char words[MAX_LEN];
    int top;
} stack;

/*
static stack stk;

Para modificar la pila, podemos definir esta variable estática o pasar la pila a las funciones como puntero.

También está la opción de implementarla con una lista enlazada (nodos con una referencia al siguiente y el contenido en char).
Para añadir, lo hacemos por al final. También se elimina por el final (izquierda).
*/

// Operaciones básicas: push(char), pop(), top(), is_empty(), is_full(), reset()

void push(char c, stack *stk) {
    stk->top++;
    stk->words[stk->top] = c;
}

char pop(stack *stk) {
    return stk->words[stk->top--];
}

// en estas operaciones, stk es const porque no la modifican

char top(const stack *stk) {
    return stk->words[stk->top];
}

int is_empty(const stack *stk) {
    return (stk->top == EMPTY);
}

int is_full(const stack *stk) {
    return !(is_empty(stk));
}

void reset(stack *stk) {
    stk->top = EMPTY;
}

// programa principal para hacer reverse a una cadena

int main() {
    stack stk;
    char *str_to_reverse = "hola me llamo Jorge";
    char reversed_str[MAX_LEN];
    int i = 0;

    reset(&stk);
    printf("\nOriginal string is: %s\n", str_to_reverse);

    while (*str_to_reverse != '\0') {
        push(*str_to_reverse++, &stk);
    }

    while (!is_empty(&stk)) {
        reversed_str[i++] = pop(&stk);
    }

    printf("The reversed string is: %s\n", reversed_str);
}
