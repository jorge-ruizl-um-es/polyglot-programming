# include <stdio.h>
# include <math.h>      // para atof() --> convertir de cadena a punto flotante en doble precision
# include <ctype.h>
# include <string.h>

# define MAXLEN 100  
# define NUMBER '0'     // señal de que un número se encontró
# define FUNCTION '1'   // señal de que se encontró una función
# define MAXVAL 100     // máxima profundidad de la pila val

// declaración de funciones
int getline(char []);
int getop(char []);
void push(double);
double pop(void);

// variable externa
char line[MAXLEN];      // todas las funciones van a tener acceso a la línea, así que es mejor ponerla de forma EXTERNA
int linep = 0;      // puntero que marca por dónde vamos al leer una linea

/* programa principal: calculadora polaca inversa */
int main()
{
    int type, index = 0;
    double op1, op2, recent=0;
    char s[MAXLEN];
    
    while (getline(line) > 0) {
        linep = 0;
        while ((type = getop(s)) != '\0') {
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
                    printf("\t%.8g\n", recent);
                    break;
                
                default:
                    printf("error: comando desconocido\n");
                    break;
            }
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

int getop(char s[])
{
    int i, c;

    while ((s[0] = c = line[linep++]) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (!isdigit(c) && c!='.' && !isalpha(c)){
        return c;   // es un operador
    }

    i = 0;

    if (isalpha(c)) {
        while(isalpha(s[++i] = c = line[linep++]))
            ;
        s[i] = '\0';
        linep--;
        return FUNCTION;
    }

    if (isdigit(c))     // reune la parte entera (ya se ha guardado de antes en s con el primer while)
        while(isdigit(s[++i] = c = line[linep++]))
            ;
    if (c=='.')     // reune la parte fraccionaria
        while (isdigit(s[++i] = c = line[linep++]))
            ;

    s[i] = '\0';  // finaliza la cadena sustituyendo el último caracter leido y almacenado por null, ya que no es un digito
    linep--;
    return NUMBER;
}

int getline(char s[])
{
    int c, i;

    for (i = 0; i < MAXLEN-1 && (c = getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    
    if (c == '\n')
        s[i++] = c;
    
    s[i] = '\0';
    return i;
}
