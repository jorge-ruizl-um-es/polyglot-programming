# include <stdio.h>
# include "calc.h"

int getline(char s[])
{
    int c, i;

    for (i = 0; i < MAXLEN-1 && (c = getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    
    if (c == '\n')
        s[i++] = c;
    
    s[i] = '\0';
    return i;
}