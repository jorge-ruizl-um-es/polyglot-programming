# include <stdio.h>
# include <ctype.h>

# define MAX_LEN 20
# define PALABRA 1
# define NO_PALABRA 0

int main()
{
    /* primero, hacemos que el programa pueda almacenar un array de longitudes de palabras hasta 20 letras */

    int c, count, state;
    int longitudes[MAX_LEN+1];

    state = NO_PALABRA;
    count = 0;

    for (int i=0; i<=MAX_LEN; i++)
        longitudes[i]=0;    // inicializar array
    
    while((c = getchar()) != EOF) {
        if (isspace(c)) {
            if (state = PALABRA) {
                state = NO_PALABRA;
                if (count <= MAX_LEN)
                    ++longitudes[count];
            }
            count = 0;
        }

        else {
            count ++;
            state = PALABRA;
        }
    } 

    /* una vez tenemos el array con las longitudes, montamos el histograma */

    for (int j = MAX_LEN; j > 0; j--){      /* no va a haber palabras de longitud 0 */
        printf("%2d  |  ", j);
        for (int k = 1; k <= longitudes[j]; k++)
            printf("#");
        printf("\n");
    }
}