# include <stdio.h>

// shellsort: ordena un array de entero de menor a mayor
void shellsort(int v[], int n);

void shellsort(int v[], int n)
{
    int gap, i, j, temp;

    for (gap = n/2; gap > 0; gap /= 2)
        for (i = gap; i<n; i++)
            for (j=i-gap; j>=0 && v[j] > v[j+gap]; j-=gap){
                temp = v[j];
                v[j] = v[j+gap];
                v[j+gap] = temp;
            }
}

/* 
FUNCIONAMIENTO:

Tenemos tres bucles for. El primero inicializa el espacio entre elementos, que ira decrementando a razon de dos.
El segundo bucle recorre el array desde donde marque gap, y el tercero compara elementos separados por el espacio del primer
bucle, detectando si el elemento de por debajo es mayor, e intercambiando las posiciones para reordenarlos si es asi. 
*/

int main()
{
    int i;
    int c[] = {23, 1, 439, 98, 23, 9, 0, 234};
    shellsort(c, 8);
    for (i=0; i<8; ++i)
        printf("%d\n", c[i]);
}