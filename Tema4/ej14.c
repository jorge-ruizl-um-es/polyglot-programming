# include <stdio.h>

# define swap(t, x, y) t _temp = x; x = y; y = _temp;

int main() {
    int a = 1, b = 2;
    swap(int, a, b);
    printf("Valor de a: %d; valor de b; %d", a, b);
    return 0;
}