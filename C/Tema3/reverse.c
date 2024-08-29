# include <stdio.h>
# include <string.h>

/* funcion reverse utilizando el operador , */

void reverse(char s[])
{
    int c, i, j;

    for (i=0, j=strlen(s)-1; i<j; i++, j--){
        c = s[i];
        s[i] = s[j];
        s[j] = c;
        // otra forma con comas --> c=s[i], s[i] = s[j], s[j] = c
    }
}

void reverse2(char s1[], char s2[])
{
    int i=strlen(s1)-1;
    int j = 0;

    while (i>=0)
        s2[j++] = s1[i--];
}

int main()
{
    char s1[] = "Hola mundo xd";
    char s2[strlen(s1)];

    //reverse(s1);
    //printf("%s", s1);
    reverse2(s1, s2);
    printf("%s", s2);
}