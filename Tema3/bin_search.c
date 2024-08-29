# include <stdio.h>
# include <string.h>

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

    while (up!=down && found==-1){
        mid = (up+down)/2;
        if (x<v[mid]){
            up = mid-1;
        }
        else if (x>v[mid]){
            down = mid+1;
        }
        else{
            found = mid;
        }
    }

    if (found == -1){       // esto se dará si el bucle se cierra porque up==down
        found = ((x==v[up]) ? up : -1);
    }

    return found;
}

int main()
{
    int v[] = {1, 4, 5, 8, 12, 15, 16, 17, 19};
    printf("%2d", bin_search(17, v, 9));
}