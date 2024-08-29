# include <stdio.h>

/* funcion para concaternar dos cadenas */

void str_cat(char s[], char t[]);

void str_cat(char s[], char t[])
{
    int i, j;

    i = j = 0;

    while (s[i]!='\0')
        ++i;
    
    while((s[i++] = t[j++])!='\0')
        ;
}

int main()
{
    char s[] = "Holaa xd ";
    char t[] = "mi nombre es Jorge";

    str_cat(s, t);
    printf("%s", s);
}