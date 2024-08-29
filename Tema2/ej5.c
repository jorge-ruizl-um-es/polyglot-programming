# include <stdio.h>

/* funcion any(s1, s2), que devuelve la primera posicion de s1 con un caracter de s2, o -1 si no hay ninguno */

int any(char s1[], char s2[]);
int char_in_str(char c, char s[]);

int char_in_str(char c, char s[])
{
    int i = 0;
    int found = 0;

    while (s[i]!='\0' && !found)
        if (s[i++]==c)
            found = 1;
    return found;
}

int any(char s1[], char s2[])
{
    int i, j;
    int output = -1;

    for (i = 0; s1[i]!='\0' && output==-1; ++i)
        if (char_in_str(s1[i], s2))
            output = i;
    return output;
}

int main()
{
    char s[] = "Hola mundo";
    char s2[] = "peste y peos";
    int i = any(s, s2);

    printf("%d", i);
    printf("%c", s[i]);
}