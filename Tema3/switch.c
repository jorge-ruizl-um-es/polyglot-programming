# include <stdio.h>

/* programa para contar digitos, espacios en blanco, y caracteres cualesquiera con un switch */

int main()
{
    int i, c, nwhite, nother, ndigit[10];
    nwhite = nother = 0;

    for (i=0; i<10; ++i)
        ndigit[i] = 0;  // inicializar array
    
    while ((c = getchar()) != EOF) {
        switch(c){
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':   // forzar fall through distintos case hasta alcanzar break
            ndigit[c-'0']++;    // ASCII de c menos ASCII de 0 devuelve el numero del 0 al 9
            break;

            case ' ': case '\n': case '\t':
                ++nwhite;
                break;
            
            default:
                nother++;
                break;
        }
    }

    printf("digitos =");
    for (i=0; i<10; i++)
        printf(" %d", ndigit[i]);
    printf(", espacios en blanco = %d, otros = %d\n", nwhite, nother);
    return 0;

}