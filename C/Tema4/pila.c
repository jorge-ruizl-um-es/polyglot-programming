# include <stdio.h>
# include <math.h>      // para atof() --> convertir de cadena a punto flotante en doble precision
# include <ctype.h>

# define MAXVAL 100     // máxima profundidad de la pila val

void push(double);
double pop(void);
double top(void);
void clear(void);
void change(void);
void duplicate_top(void);

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

double top(void)
{
    if (sp>0)
        return val[sp-1];
    else
        printf("Error: pila vacia \n");
}

void clear(void)
{
    while (sp>0){
        sp--;
    }
}

void change(void)
{
    if (sp>=2){
        double el1, el2;

        el2 = pop();
        el1 = pop();
        push(el2);
        push(el1);
    }
    else
        printf("Error: no hay suficientes elementos como para hacer la operacion change\n");
}

void duplicate_top(void)
{
    if (sp>0) {
        push(top());
    }
    else
        printf("Error: pila vacia \n");
}


int main()
{
    double arr[] = {1.0, 2.0, 3.0, 4.0};

    for (int i=0; i<4; ++i)
        push(arr[i]);
    printf("%g\n", top());
    duplicate_top();
    printf("%g\n", pop());
    printf("%g", top());
}
