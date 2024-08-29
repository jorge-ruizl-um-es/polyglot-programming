# include <stdio.h>
# include <ctype.h>
# include <math.h>

# define STACKSIZE 10000

// programa expr para evaluar expresión polaca inversa donde cada operador es un argumento de la función
// Uso: expr 2 3 4 + * --> 2 * (3 + 4)

void push(float);
float pop(void);

int is_number (char *s) {
    int i = 0;
    char c, next;
    int sign;
    while (isspace(c = s[i]))
        i++;

    if (c=='-' || c=='+') {
        c = s[++i];
    }
    if (c == '\0')
        return 0;
    
    for (; s[i] != '\0'; i++) {
        if (!isdigit(s[i]) && s[i]!='.')
            return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    int c;
    float scnd;
    char **p = argv + 1; // apunta al primer argumento

    // primero se le quita uno para no contar "expr"
    while (--argc && p < argv + argc) {
        if (is_number(*p)) {
            printf("%f\n", atof(*p));
            push(atof(*p++));
        }
        else {
            c = *p[0]; // = **p;
            printf("%c\n", c);
            switch (c) {
                case '+':
                    push(pop() + pop());
                    break;
                case 'x':
                    push(pop() * pop());
                    break;
                case '-':
                    scnd = pop();
                    push(pop()-scnd);
                    break;
                case '/':
                    scnd = pop();
                    push(pop()/scnd);
                    break;
                default:
                    printf("error: comando desconocido %s\n", c);
                    return -1;
            }
            p++;
        }
    }
    printf("Resultado: %f\n", pop());
    return 0;
}

float stack[STACKSIZE];
float *stackp = stack;

void push(float i) {
    if (stackp >= stack && stackp < stack + STACKSIZE)
        *stackp++ = i;
    else
        printf("push: error al introducir elemento en la pila\n");
}

float pop(void) {
    if (stackp>stack)
        return *--stackp;
    else
        printf("pop: error al sacar un elemento de una pila vacia\n");
}