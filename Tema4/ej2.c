# include <stdio.h>
# include <ctype.h>

double atof(char s[]);

/* atof convierte cadena s a un punto flotante de doble precision double */

double atof(char s[])
{
    double val, power=1.0;
    int i, j, sign, power_sign, power_num;

    for (i=0; isspace(s[i]); i++)
        ;
    
    sign = (s[i]=='-') ? -1 : 1;

    if (s[i]=='+' || s[i]=='-')
        i++;
    
    for (val=0.0; isdigit(s[i]); i++)
        val = 10.0*val + (double)(s[i]-'0');

    if (s[i] == '.' || s[i] == ','){
        ++i;
        for (power=1; isdigit(s[i]); i++) {
            val = 10.0*val + (s[i]-'0');
            power *= 10;
        }
    }

    if (s[i]=='e' || s[i]=='E'){
        i++;
        power_sign = (s[i]=='-') ? -1 : 1;
        if (s[i]=='-' || s[i]=='+')
            i++;
        for (power_num=0; isdigit(s[i]); i++)
            power_num = 10*power_num + (s[i]-'0');
        if (power_sign>0){
            for (j=0; j<power_num; j++){
                power/=10;
            }
        }
        else{
            for (j=0; j<power_num; j++){
                power*=10;
            }
        }
    }    
    return (val/power)*sign;
}

int main()
{
    char s[] = "  -1.23E2";
    printf("%g", atof(s));
}