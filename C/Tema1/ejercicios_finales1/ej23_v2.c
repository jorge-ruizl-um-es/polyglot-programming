# include <stdio.h>

/* programa para eliminar los comentarios de otro programa en C*/

# define LIMIT 200000

int getline(char line[]);
int remove_comments(char line[], char new_line[], int len, int in_comment_paragraph);
int copy_to_database(char input[], char database[], int index);

int main() {

    char full_text[LIMIT];
    char line[LIMIT];
    char new_line[LIMIT];
    int len, i, in_comment;

    in_comment = i = 0;
    
    while ((len = getline(line)) > 0 ){
        in_comment = remove_comments(line, new_line, len, in_comment);
        i = copy_to_database(new_line, full_text, i);
    }

    printf("%s", full_text);
}

int getline(char line[]) {
    int c, i = 0;

    while ((c = getchar()) != EOF && c != '\n' && i < LIMIT - 1) {
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

int remove_comments(char line[], char new_line[], int len, int in_comment_paragraph)
{
    int i, a, in_comment_line;
    in_comment_line= a = 0;

    for (i=0; i<len-1; ++i) {
        if (line[i] == '/' && line[i+1] == '*' && in_comment_paragraph==0)
            in_comment_paragraph = 1;
        else if (line[i]!='/' && in_comment_paragraph==0 && in_comment_line==0){
            new_line[a] = line[i];
            a++;
        }
        else if (line[i] == '*' && line[i+1] == '/' && in_comment_paragraph==1)
            in_comment_paragraph = 0;

        else if (line[i] == '/' && line[i+1] == '/' && in_comment_line==0)
            in_comment_line = 1;
    }

    if (a!=0){
        new_line[a] = '\n'; // añadir salto de linea a las nuevas lineas sin comentarios
        new_line[a+1] = '\0';
    }
    else
        new_line[a] = '\0'; // eliminar las lineas que queden vacias
    return in_comment_paragraph;
}

int copy_to_database(char input[], char database[], int index)
{
    int j = 0;

    while (input[j]!='\0'){
        database[index+j] = input[j];
        ++j;
    }

    database[index+j]='\0';
    return index+j;
}