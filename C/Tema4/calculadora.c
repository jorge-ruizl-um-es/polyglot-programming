# include <stdio.h>
# include <math.h>      // para atof() --> convertir de cadena a punto flotante en doble precision
# include <ctype.h>
# include <string.h>

# define MAXLEN 100  
# define NUMBER '0'     // señal de que un número se encontró
# define FUNCTION '1'   // señal de que se encontró una función
# define MAXVAL 100     // máxima profundidad de la pila val

// declaración de funciones
int getop(char []);
void push(double);
double pop(void);

/* programa principal: calculadora polaca inversa */
int main()
{
    int type;
    double op1, op2, recent=0;
    char s[MAXLEN];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            
            case FUNCTION:
                if (strcmp(s,"sin")==0)
                    push(sin(pop()));
                else if (strcmp(s,"exp")==0)
                    push(exp(pop()));
                else if (strcmp(s,"pow")==0){
                    op2 = pop();
                    push(pow(pop(), op2));
                }
                else if (strlen(s)==1){
                    int c = s[0];
                    if (c=='r')
                        (recent == 0) ? printf("Recent not defined\n") : push(recent);
                    else if (c>='a' && c<='z')
                        push(c);
                }
                else
                    printf("Funcion o variable no reconocida\n");
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
            
            case '%':
                op2 = pop();
                op1 = pop();
                if ((op2==(int)op2 && op1==(int)op1) && op2!=0)
                    push((int)op1 % (int)op2);
                else
                    printf("error: operandos invalidos para la operacion modulo\n");
                break;
            
            case '\n':
                recent = pop();
                printf("\t%.8g\n", recent);     // imprimir double con 8 decimales
                break;
            
            default:
                printf("error: comando desconocido\n");
                break;
        }
    }
    return 0;
}




// variables externas a las que tienen que tener acceso simultáneo tanto push como pop. Pueden estar ocultas a main porque no accede a ellas
// al estar declaradas después de main, si quisieramos hacerlas visibles para main deberíamos usar extern
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
    int i, c, c_sig;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (!isdigit(c) && c!='.' && c!='-' && !isalpha(c)){
        return c;   // es un operador
    }

    i = 0;

    if (c=='-' && !isdigit(c_sig = getch())){
        ungetch(c_sig);
        return c;
    }
    else if (c == '-' && isdigit(c_sig)) {
        s[++i] = c_sig;
        while(isdigit(s[++i] = c = getch()))
            ;
    }

    if (isalpha(c)) {
        while(isalpha(s[++i] = c = getch()))
            ;
        s[i] = '\0';
        if (c!=EOF)
            ungetch(c);
        return FUNCTION;
    }

    if (isdigit(c))     // reune la parte entera (ya se ha guardado de antes en s con el primer while)
        while(isdigit(s[++i] = c = getch()))
            ;
    if (c=='.')     // reune la parte fraccionaria
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';  // finaliza la cadena sustituyendo el último caracter leido y almacenado por null, ya que no es un digito
    if (c!=EOF)
        ungetch(c);   // se almacena el último carácter leído en el buffer, de forma que en la siguiente llamada a getch se leerá este,
                    // y luego seguirá leyéndose de teclado por donde nos habíamos quedado en la línea.
    return NUMBER;
}

/*
Las funciones getch y ungetch funcionan conjuntamente para obtener el numero completo en forma de cadena. 
El problema de hacerlo normalmente (con getchar) sería que solo se leería el primer número de una línea, descartando lo demás.
La solución a esto es emplear un buffer con dos funciones auxiliares para getop:
    - getop --> devuelve un operando leído o una señal de que ha leído un número almacenado en la cadena s.
        Va leyendo de teclado o en su defecto de un buffer donde se almacena el último caracter leido no almacenado en s
    - getch --> devuelve un caracter leido por teclado si el buffer está vacío, o un caracter del buffer si lo hay
    - ungetch --> almacena un caracter leido en el buffer
*/

# define BUFSIZE 100

char buffer[BUFSIZE];
int bufp = 0;   // siguiente posicion vacia del buffer

int getch(void)
{
    return (bufp>0) ? buffer[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp>=BUFSIZE)  
        printf("Error en ungetch");
    else
        buffer[bufp++] = c;
}
