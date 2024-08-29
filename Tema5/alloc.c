# include <stdio.h>

# define ALLOCSIZE 10000    // tamaño disponible en memoria para el programa

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;     // puntero a la primera posición de allocbuf

char *alloc(int n) {    // la función devuelve un puntero a la primera posición de los n caracteres almacenados
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        // comprobamos si hay espacio (posición 0 + tamaño máximo - espacio usado)
        allocp += n;    // ocupamos el espacio marcado
        return allocp - n;
    }
    else 
        return 0;   // regresa 0 si no puede reservarse espacio para n caracteres (0 no es una dirección de memoria valida)
}

void afree(char *p) {   // si p está entre la posición inicial y final del buffer, haces allocp = p
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}