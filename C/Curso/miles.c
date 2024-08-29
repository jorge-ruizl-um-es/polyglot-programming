# include <stdio.h>

int main() {
    int miles, yards;
    double kilometers;

    printf("Introduce the maraton's lenght in miles and yards:\n");
    scanf("%d%d", &miles, &yards);

    kilometers = 1.609 * (miles + yards/1760.0);
    printf("\nThe maraton is %lf km\n", kilometers);
    return 0;
}