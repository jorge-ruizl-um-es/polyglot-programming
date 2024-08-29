# include <stdio.h>

/* funcion squeeze(s1, s2) para borrar todo caracter de s1 que esté en s2 */

void squeeze(char s1[], char s2[]);
int char_in_str(char c, char s[]);

int char_in_str(char c, char s[])
{
    int i = 0;
    int found = 0;

    while (s[i]!='\0' && found==0)
        if (s[i++]==c)
            found = 1;
    return found;
}

void squeeze(char s1[], char s2[])
{
    int i, j;

    for (i = j = 0; s1[i]!='\0'; ++i)
        if (!char_in_str(s1[i], s2))
            s1[j++] = s1[i]; // deshechas lo que había antes en la cadena para ir construyendo una nueva en la misma variable
    s1[j] = '\0';
}

int main()
{
    char s[] = "Hola mundo";
    char s2[] = "peste y peos";
    squeeze(s, s2);
    printf("%s", s);
}