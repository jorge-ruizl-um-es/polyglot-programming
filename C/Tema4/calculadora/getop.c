# include <stdio.h>
# include <ctype.h>
# include "calc.h"

extern char line[];
extern int linep;

int getop(char s[]) {
    int c, c_sig, i;

    while ((s[0] = c = line[linep++]) == ' ' || c == '\t')
        ;
    
    s[1] = '\0';

    if (!isdigit(c) && !isalpha(c) && c!='.')
        return c;   // operador

    i = 0;

    if (isalpha(c)) {
        while(isalpha(s[++i] = c = line[linep++]))
            ;
        s[i] = '\0';
        linep--;
        return FUNCTION;
    }

    if (isdigit(c))     // reune la parte entera (ya se ha guardado de antes en s con el primer while)
        while(isdigit(s[++i] = c = line[linep++]))
            ;
    if (c=='.')     // reune la parte fraccionaria
        while (isdigit(s[++i] = c = line[linep++]))
            ;

    s[i] = '\0';  // finaliza la cadena sustituyendo el último caracter leido y almacenado por null, ya que no es un digito
    linep--;
    return NUMBER;
}