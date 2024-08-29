# include <stdio.h>

# define SIZE 8

void print_array(int how_many, int array[]) {
    for (int i = 0; i < how_many; i++) {
        printf("%d\t", array[i]);
    }
    printf("\n");
}

void merge(int a[], int b[], int c[], int how_many) {   // a y b tendrán el mismo tamaño
    int i, j, k;
    i = j = k = 0;

    while (i<how_many && j<how_many) {
        if (a[i] < b[j]) {
            c[k++] = a[i++];
        }
        else
            c[k++] = b[j++];
    }

    // cleanup
    while (i<how_many) {
        c[k++] = a[i++];
    }

    while (j < how_many) {
        c[k++] = b[j++];
    }
}

void mergesort(int key[], int how_many) {
    int i, j;
    int w[how_many];

    for (i = 1; i < how_many; i*=2) {
        for (j = 0; j < how_many-i; j += 2*i)
            merge(key+j, key+j+i, w+j, i);
        for (j = 0; j < how_many; j++) 
            key[j] = w[j];
    }
}

int main() {
    int grades[SIZE] = {99, 82, 74, 85, 92, 67, 76, 49};
    print_array(SIZE, grades);
    printf("\n");
    mergesort(grades, SIZE);
    print_array(SIZE, grades);
    return 0;
}