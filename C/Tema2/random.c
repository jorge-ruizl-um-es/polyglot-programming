# include <stdio.h>

int rand(void);
void rand_seed(unsigned int seed);

unsigned long int next = 1;     // variable externa

void rand_seed(unsigned int seed) 
{
    next = seed;
}

int rand(void)
{
    next = next*1103515245 + 12345;
    // se hace un escalado hacia abajo de next, que al ser long puede ser un numero muy grande
    // se aplica el casting para convertirlo a int una vez reducido el rango de valores de next con el escalado
    // asi, aunque el resultado de la division siga siendo grande, se fuerza a reducir el numero de bits con el cast
    return (unsigned int)(next/65536) % 32768;
}   

int main()
{
    rand_seed(42343);
    printf("%d", rand());
}