#include <stdio.h>

/*Constantes simbólicas*/
# define inicio 300
# define fin 0
# define salto -20

void main()
{
    int fahr;
    /*int inicio, fin, salto;*/

    /*
    inicio = 300;
    fin = 0;
    salto = -20;
    */

    for (fahr=inicio; fahr>=fin; fahr+=salto)
        printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));

}