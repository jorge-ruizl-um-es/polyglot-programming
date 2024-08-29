# include <stdio.h>
# include <math.h>
# include <string.h>
# include "calc.h"

char line[MAXLEN];
int linep;

int main() {
    
    int type;
    double op1, op2, recent=0.0;
    char s[MAXLEN];

    while (getline(line)>0)
        linep = 0;
        while ((type = getop(s)) != '\0'){
            switch (type) {
                case NUMBER:
                    push(atof(s));
                    break;
                
                case FUNCTION:
                    if (strcmp(s,"sin")==0)
                        push(sin(pop()));
                    else if (strcmp(s,"exp")==0)
                        push(exp(pop()));
                    else if (strcmp(s,"pow")==0){
                        op2 = pop();
                        push(pow(pop(), op2));
                    }
                    else if (strlen(s)==1){
                        int c = s[0];
                        if (c=='r')
                            (recent == 0) ? printf("Recent not defined\n") : push(recent);
                        else if (c>='a' && c<='z')
                            push(c);
                    }
                    else
                        printf("Funcion o variable no reconocida\n");
                    break;
                
                case '+':
                    push(pop() + pop());
                    break;
                
                case '*':
                    push(pop()*pop());
                    break;
                
                case '-':
                    op2 = pop();
                    push(pop()-op2);
                    break;
                
                case '/':
                    op2 = pop();
                    if (op2!=0.0)
                        push(pop()/op2);
                    else
                        printf("error: division entre cero\n");
                    break;
                
                case '%':
                    op2 = pop();
                    op1 = pop();
                    if ((op2==(int)op2 && op1==(int)op1) && op2!=0)
                        push((int)op1 % (int)op2);
                    else
                        printf("error: operandos invalidos para la operacion modulo\n");
                    break;
                
                case '\n':
                    recent = pop();
                    printf("\t%.8g\n", recent);
                    break;
                
                default:
                    printf("error: comando desconocido\n");
                    break;
            }
        }
        return 0;
}