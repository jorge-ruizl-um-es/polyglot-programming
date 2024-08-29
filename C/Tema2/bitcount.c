# include <stdio.h>

// funciones que cuentan el numero de bits en 1 que tiene un elemento unsigned
int bitcount1(unsigned x);
int bitcount2(unsigned x);
// el argumento de la funcion es un unsigned para que al correrlo a la derecha siempre se añadan 0

int bitcount1(unsigned x)
{
    int b;

    for (b=0; x!=0; x >>= 1)
        if (x & 1)      // esto compara el bit menos significativo de x con 1 --> si ambos son 1 devuelve 1
            b++;

    return b;
}

int bitcount2(unsigned x)
{
    int b = 0;

    while (x!=0) {
        x &= (x-1);
        b++;
    }

    return b;
}

int main()
{
    unsigned int x = 13;
    printf("%d\n%d\n", bitcount1(x), bitcount2(x));
}