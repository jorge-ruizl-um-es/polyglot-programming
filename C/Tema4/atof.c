# include <stdio.h>
# include <ctype.h>

double atof(char s[]);

/* atof convierte cadena s a un punto flotante de doble precision double */

double atof(char s[])
{
    double val;
    int i, sign, power;

    for (i=0; isspace(s[i]); i++)
        ;
    
    sign = (s[i]=='-') ? -1 : 1;

    if (s[i]=='+' || s[i]=='-')
        i++;
    
    for (val=0.0; isdigit(s[i]); i++)
        val = 10.0*val + (double)(s[i]-'0');
    if (s[i] == '.' || s[i] == ',')
        ++i;
    for (power=1; isdigit(s[i]); i++) {
        val = 10.0*val + (s[i]-'0');
        power *= 10;
    }
    return (val/power)*sign;
}

int main()
{
    char s[] = "  -12.345";
    printf("%g", atof(s));
}