# include <stdio.h>
# include "calc.h"

# define MAXVAL 1000 

// variables externas utilizables solo por push y pop
int sp = 0;
double val[MAXVAL];

// las funciones ya se han declarado en .h

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