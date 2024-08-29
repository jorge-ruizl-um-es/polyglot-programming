# include <stdio.h>

/*
v.1

int main (int argc, char *argv[]) {
    int i=1; // el 0 es para el nombre del programa al que se invoca

    while (i<argc) {
        printf("%s%s", argv[i], (i < argc-1)? " " : "");
        i++;
    }
    printf("\n");
    return 0;
}
*/

int main (int argc, char *argv[]) {
    while (--argc)
        // primero incrementar argv pq argv[0] no se imprime
        printf("%s%s", *++argv, (argc>1)? " " : "");
        // otra forma: printf((argc>1) ? "%s " : "%s", *++argv);
    printf("\n");
    return 0;
}