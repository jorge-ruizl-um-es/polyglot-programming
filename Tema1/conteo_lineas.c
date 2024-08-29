# include <stdio.h>

int main()
{
    int lineas, esp, tab, c;

    lineas=0;
    esp=0;
    tab=0;
    while ((c=getchar())!=EOF){
        if (c=='\n')
            lineas ++;
        if (c==' ')
            esp++;
        if (c=='\t')
            tab++; 
    }
    return 0;
    printf("El input tiene %d nuevas lineas, %d espacios en blanco y %d tabulaciones\n", lineas, esp, tab);
}