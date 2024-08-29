# include <stdio.h>

/* 
programa que verifica la correccion sintactica de otro programa en C 

funcionalidades: 
    - detecta correcta alineacion de parentesis, corchetes y llaves --> funcion is_aligned --> HECHO
    - detecta correcta alineacion de comillas y apostrofos --> HECHO
    - detecta correcta alineacion de comentarios de varias lineas --> funcion check_comments --> HECHO
    - detecta correcto uso de secuencias de escape --> funciones char_in_array y escape_sentences (dificil)

    - Idea para añadir: que te corrija los errores de alineacion
*/

# define MAXLEN 2000000
# define ARRAY_SIZE 12

// definicion de las funciones a utilizar
int get_text(char line[]);

// funciones que devuelven 1 o 0 (hacen de booleanos)
int is_aligned(char line[]);
int check_comments(char line[], int len);
int char_in_array(char a);
int escape_seq(char array[], int size);

// programa principal

int main()
{
    int len;
    char line[MAXLEN];
    int alineation, comments, escape;

    alineation = comments = escape = 1;

    len = get_text(line);
    alineation = is_aligned(line);
    comments = check_comments(line, len);
    escape = escape_seq(line, len);
    
    if (alineation==1 && comments==1 && escape==1)
        printf("Codigo correcto\n");

    if (alineation==0){
        printf("Error en la alineacion de parentesis, corchetes o llaves del codigo\n");
    }
    if (comments==0) {
        printf("Error en la apertura y cierre de comentarios multi-linea\n");
    }
    if (escape==0) {
        printf("Uso de una secuencia de escape inexistente\n");
    }

    return 0;
}

// funcion de lectura

int get_text(char line[]) {
    int c, i = 0;

    while ((c = getchar()) != EOF && i < MAXLEN - 1) {
        line[i] = c;
        ++i;
    }

    line[i] = '\0'; // añadir caracter que indica el fin de la cadena

    return i;
}

// funciones de correccion

int is_aligned(char line[])
{
    int i, counterp, counterk, counterC, countera, countercom, correct, open_ap, open_com;

    correct = 0;
    open_ap = open_com = 0;

    i = counterp = counterk = counterC = countera = countercom = 0;
    while (line[i]!='\0'){
        if (line[i]=='(')
            ++counterp;
        else if (line[i]==')')
            --counterp;

        else if (line[i]=='{')
            ++counterk;
        else if (line[i]=='}')
            --counterk;

        else if (line[i]=='[')
            ++counterC;
        else if (line[i]==']')
            --counterC;
        
        else if (line[i] == '\'' && open_ap == 0){
            open_ap = 1;
            ++countera;
        }
        else if (line[i] == '\'' && open_ap == 1){
            open_ap = 0;
            --countera;
        }

        else if (line[i] == '\"' && open_com == 0){
            open_com = 1;
            ++countercom;
        }
        else if (line[i] == '\"' && open_com == 1){
            open_com = 0;
            --countercom;
        }

        ++i;
    }

    if (counterp == 0 && counterk == 0 && counterC == 0 && countera == 0 && countercom == 0)
        correct = 1;
    
    return correct;
}

int check_comments(char line[], int len)
{
    int i, counter, correct;

    counter = correct = 0;

    for (i=0; i<len-1; ++i) {
        if (line[i] == '/' && line[i+1] == '*')
            ++counter;

        else if (line[i] == '*' && line[i+1] == '/')
            --counter;
    }

    if (counter == 0)
        correct = 1;
    
    return correct;
}

int escape_seq(char line[], int size)
{
    int i, correct, a, found;

    correct = 1;

    for (i=0; i<size-1; ++i) {
        if (line[i] == '\\') {
            found = 0;
            a = line[i+1];
            found = char_in_array(a);
            if (found == 0)
                correct = 0;
        }
    }

    return correct;
}

// funcion auxiliar para comprobar si un caracter está en un array

int char_in_array(char a)
{
    char seq_array[ARRAY_SIZE] = {'a', 'b', 'f', 'n', 'r', 't', 'v', '\'', '\"', '\\', '?', '0'};
    int i, found;

    found = 0;

    for (i=0; i<=ARRAY_SIZE; ++i){
        if (seq_array[i] == a)
            found = 1;
    }
    return found;
}