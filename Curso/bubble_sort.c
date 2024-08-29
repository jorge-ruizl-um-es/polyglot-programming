# include <stdio.h>

void swap(int *i, int *j) {
    int temp;
    temp = *i;
    *i = *j;
    *j = temp;
}

void print_array(int how_many, int array[]) {
    for (int i = 0; i < how_many; i++) {
        printf("%d\t", array[i]);
    }
    printf("\n");
}

void bubble_sort(int array[], int how_many) {
    int go_on;
    int i, j;

    for (i = 0; i < how_many; i++) {
        print_array(how_many, array);
        printf("i = %d, input any int to continue: ", i);
        scanf("%d", &go_on);

        for (j = how_many-1; j > i; j--) {  // no se pone >= porque si fuera igual podríamos acceder a la posición array[-1] si i = 0
            if (array[j-1] > array[j]) {
                swap(&array[j-1], &array[j]);
            }
        }
    }
}

int main() {
    int array[] = {78, 67, 92, 83, 88};

    bubble_sort(array, 5);
    print_array(5, array);
    return 0;
}