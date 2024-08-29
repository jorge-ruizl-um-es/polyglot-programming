# include <stdio.h>

/* funcion double_line cuya longitud sea mayor que LIMIT después del último caracter no blanco antes de la n-esima columna de entrada */

# define MAXLEN 10000
# define N 10

void double_line(int n, char input[], int len, char output[]);
void double_line2(int n, char input[], int len);
int getline(char line[]);

int main()
{
    int len;
    char line[MAXLEN];
    char new_line[MAXLEN];

    while ((len = getline(line)) > 0) {
        //double_line(N, line, len, new_line);
        //printf("%s", new_line);
        double_line2(N, line, len);

    }
}

int getline(char line[]) {
    int c, i = 0;

    while ((c = getchar()) != EOF && c != '\n' && i < MAXLEN - 1) {
        line[i] = c;
        ++i;
    }

    if (c == '\n') {
        line[i] = c;
        ++i;
    }

    line[i] = '\0';

    return i;
}

void double_line(int n, char input[], int len, char output[])
{
    int i, a;

    if (len <= n)
        for (i=0; i<=len; ++i)
            output[i] = input[i];
    else
        a = 0;
        for (i=0; i<=len; ++i) {
            if (i%n == n-1) {
                while (input[i]==' ' || input[i]=='\t')
                    --i;
                output[a] = input[i];
                output[++a] = '\n';
            }
            else {
                output[a] = input[i];
            }
            ++a;
        }

}

void double_line2(int n, char input[], int len)
{
    // esta version es mas compacta pero puede cortarte por caracteres blancos
    int i;

    if (len <= n)
        printf("%s", input);
    else
        for (i=0; i<=len; ++i) {
            if (i%n == n-1 || i==len){
                while (input[i]==' ')
                    --i;
                printf("%c%c", input[i], '\n');
            }
            else
                printf("%c", input[i]);
        }

}