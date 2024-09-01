# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <math.h>

# define MAXLEN 1000

int getline(char *s) {
    int c, i=0;

    while (i < MAXLEN-1 && (c = getchar())!=EOF && c!='\n') {
        *(s+(i++)) = c;
    }

    if (c=='\n') 
        *(s+(i++)) = c;
    *(s+i) = '\0';
    return i;
}

// convertir cadena en float
float a_tof(char *s) {
    float num=0, power;
    int sign;


    while (isspace(*s))
        s++;
    sign = (*s=='-') ? -1 : 1;
    if (*s == '+' || *s == '-') 
        s++;

    while (isdigit(*s)) {
        num = 10*num + (*s-'0');
        s++;
    }
    if (*s=='.') {
        s++;
        power = 1.0;
        while (isdigit(*s)) {
            num = 10*num + (*s-'0');
            s++, power*=10.0;
        }
    }
    
    return (num/power)*sign;
}

//convertir entero a cadena
void itoa(int n, char *s) {
    int sign;
    char *p = s;
    void reverse(char *);

    if ((sign=n)<0) {
        n = -n;
    }
    
    do {
        *p++ = n%10 + '0';
    } while ((n/=10) /* != 0 */);

    *p++ = (sign<0) ? '-' : '+';
    *p = '\0';
    reverse(s);
}

void reverse(char *s) {
    char *start = s;
    char *end = s;
    char temp;

    while (*end != '\0')
        end++;
    end--;      // no incluir caracter nulo

    while (start < end) {
        temp = *start;
        *start = *end;
        *end = temp;
        start++, end--;
    }
}

// strindex (grep) para buscar patrones en lineas   

int strindex(char *source, char *pattern) {
    char *ps = source;
    char *pt;   
    char *start;

    while (*ps != '\0') {
        start = ps;
        pt = pattern;   // puntero al patrón (inicio) cada vez que se itera por source

        while (*pt != '\0' && *pt==*ps) {   // iteración y comparación entre fuente y patrón
            ps++, pt++;
        }

        if (*pt == '\0')    // se encuentra todo el patron
            return start-source;    // devuelve posicion inicial
        
        ps = start + 1;  // se recorre source
    }
    return -1;
}

// getop (calc) para ir leyendo una linea y sacando operadores
char line[MAXLEN];
char *start;
# define NUMBER '0'

int getop(char *s) {
    int c;

    while (isspace(*s = c =*start++))
        ;
    
    if (c=='\0')
        return '\0';

    *(s+1) = '\0';

    if (!isdigit(c) && c!='.')
        return c;

    if (isdigit(c)) {
        while (isdigit(c = *(++s) = *start++))
            ;
    }
    if (c=='.') {
        while (isdigit(c = *(++s) = *start++))
            ;
    }
    
    *s = '\0';

    if (c != EOF) {
        start--;
    }
    
    return NUMBER;
}

int main () {
    char s[MAXLEN] = "Hola Mundo\n";
    char t[MAXLEN] = "ndo";
    int type;
    
    while (getline(line)>0) {
        start = line;
        while ((type = getop(s)) != '\0'){
            if (type == NUMBER)
                printf("%f\n", atof(s));
            else
                printf("%c\n", type);
        }
    }
    
    //printf("%f", atof(s));
    //itoa(-1234, s);
    //printf("%s\n", s);

    //printf("%d", strindex(s, t));
}
