# include <stdio.h>

char buffer[1000];
char *pbuf = buffer;

char getch(void) {
    return (pbuf>buffer) ? *(--pbuf) : getchar(); 
}

void ungetch(char c) {
    if (pbuf > buffer + 1000)
        printf("Error");
    else
        *pbuf++ = c;
}

int main() {
    printf("%c", getch());
    ungetch('e');
    ungetch('f');
    printf("%c", getch());
}