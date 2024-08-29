# include <stdio.h>

/*
int main()
{
    int nc, c;

    nc = 0;
    while((c=getchar())!=EOF){
        if (c != '\n'){     //no contar saltos de linea
            nc++;
        }
    }
    printf("%d\n", nc);

    return 0;
}
*/

/*VERSION 2*/

int main()
{

    double nc;  // se podría haber puesto int

    for (nc = 0; (getchar() != EOF); ++nc)
    ; /*PROPOSICION NULA*/ 

    printf("%.0f\n", nc);

}