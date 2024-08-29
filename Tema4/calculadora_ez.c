# include <stdio.h>
# include <math.h>      // para atof() --> convertir de cadena a punto flotante en doble precision
# include <ctype.h>

# define MAXLEN 100  
# define NUMBER '0'     // señal de que un número se encontró
# define MAXVAL 100     // máxima profundidad de la pila val

// declaración de funciones
int getop(char []);
void push(double);
double pop(void);

/* programa principal: calculadora polaca inversa */
int main()
{
    int type;
    double op2;
    char s[MAXLEN];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            
            case '+':
                push(pop() + pop());
                break;
            
            case '*':
                push(pop()*pop());
                break;
            
            case '-':
                op2 = pop();
                push(pop()-op2);
                break;
            
            case '/':
                op2 = pop();
                if (op2!=0.0)
                    push(pop()/op2);
                else
                    printf("error: division entre cero\n");
                break;
            
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            
            default:
                printf("error: comando desconocido\n");
                break;
        }
    }
    return 0;
}




// variables externas a las que tienen que tener acceso simultáneo tanto push como pop. Pueden estar ocultas a main porque no accede a ellas
int sp = 0;     // indicador a la siguiente posición vacía de la pila
double val[MAXVAL];     // pila en sí

void push(double f)
{
    if (sp<MAXVAL)
        val[sp++] = f;  // asignar y aumentar
    else
        printf("Error: pila llena, no se puede efectuar el push de %g\n", f);
}

double pop(void)
{
    if (sp>0)
        return val[--sp];   // disminuir y retornar
    else
        printf("Error: pila vacia \n");
}


// función getop para obtener el siguiente operador u operando numérico, ignorando blancos y tabuladores

// funciones auxiliares para getop:
int getch(void);
void ungetch(int);

int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getchar()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c!='.')
        return c;   // es un operador
    i = 0;
    if (isdigit(c))     // reune la parte entera (ya se ha guardado de antes en s con el primer while)
        while(isdigit(c = getchar()))
            s[++i] = c;
    if (c=='.')     // reune la parte fraccionaria
        s[++i] = c;
        while (isdigit(c = getchar()))
            s[++i] = c;

    s[++i] = '\0';  // finaliza la cadena sustituyendo el último caracter leido y almacenado por null, ya que no es un digito
    return NUMBER;
}