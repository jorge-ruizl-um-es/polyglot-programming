# include <stdio.h>
# include <time.h>

int bin_search(int x, int v[], int len);

int bin_search(int x, int v[], int len)
{
    /* funcion que, dado un entero a buscar y un array de enteros que se supone ordenado de menor a mayor,
    regresa el indice donde se encuentra x en el array, o -1 si no está */

    int i, found;
    int up, down, mid;

    found = -1;
    down = 0;
    up = len-1;

    while (down <= up){
        mid = (up+down)/2;
        if (x<v[mid]){
            up = mid-1;
        }
        else 
            down = mid+1;
    }

    // al hacer solo una prueba, hay que verificar que el elemento encontrado es el deseado
    if (x == v[up])
        return up;
    else if (x == v[down])
        return down;
    else
        return -1;
}

int main()
{
    int v[] = {1, 4, 5, 8, 12, 15, 16, 17, 19, 21, 24, 27, 30, 31, 32, 33, 56, 77, 83, 99, 123, 234, 345, 456};
    int x = 15;
    int len = 24;

    printf("El indice de %d es: %d\n", x, bin_search(x, v, len));

}