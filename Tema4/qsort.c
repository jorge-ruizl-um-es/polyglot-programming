# include <stdio.h>

/* funcion recursiva qsort para ordenar un array numérico de menor a mayor */

void qsort(int v[], int left, int right){      // left y right son posiciones del array (inicialmente 0 y len-1)
    int i, last;
    void swap(int [], int, int);

    if (left >= right)
        return;     // no hace nada si el array tiene un elemento o menos 
    
    swap(v, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (v[i] < v[left])
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

void swap(int v[], int i, int j) {  // intercambia los elementos en las posiciones i, j de un array v
    int _temp;

    _temp = v[i];
    v[i] = v[j];
    v[j] = _temp;
}