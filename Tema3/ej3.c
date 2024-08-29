# include <stdio.h>
# include <string.h>
# include <ctype.h>

// funcion expand(s1,s2) para expandir expresiones abreviadas en s1 (a-z) a su forma equivalente en s2 (abc..xyz)

void expand(char s1[], char s2[]);

void expand(char s1[], char s2[])
{
    int i, j=0, k, fin;

    for (i=0; i<strlen(s1)-2; ++i){     // le restas 2 para ignorar \n y \0

        if (isdigit(s1[i]) && s1[i+1]=='-') {
            k = s1[i];
            fin = s1[i+2];
            while (k>='0' && k<fin){
                s2[j] = k;
                j++, k++; // aumentar array de "salida"
            }
            i++; // ignorar guion
        } 

        else if ((s1[i]>='a' && s1[i]<='z' && s1[i+1]=='-') || (s1[i]>='A' && s1[i]<='Z' && s1[i+1]=='-')) {
            k = s1[i];
            fin = s1[i+2];
            while ((k>='a' && k<fin) || (k>='A' && k<fin)){
                s2[j] = k;
                j++, k++;
            }
            i++;
        }

        else
            s2[j++] = s1[i];
    }
    s2[j++] = s1[i];
    s2[j++] = '\n';
    s2[j] = '\0';
}

void expand2(char *s1, char *s2) {
    while (*s1 != '\0' && *s1 != '\n') {
        if (isdigit(*s1) && *(s1+1)=='-') {
            int inicio = *s1;
            int fin = *(s1+2);
            
            while (inicio >= '0' && inicio < fin) {
                *s2++ = inicio++;
            }
            s1++;
        }

        else if (isalpha(*s1) && *(s1+1)=='-') {
            int inicio = *s1;
            int fin = *(s1+2);
            
            while ((inicio >= 'a' && inicio < fin) || (inicio >= 'A' && inicio < fin)) {
                *s2++ = inicio++;
            }
            s1++;
        }

        else
            *s2++ = *s1;
        s1++;
    }
}

int main()
{
    char s1[] = "Hola esto es a-z; a-b-c; f-zS-W2-8 ; -a-f";
    char s2[100000];
    expand2(s1, s2);
    printf("%s", s2);
}