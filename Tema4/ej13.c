# include <stdio.h>
# include <string.h>

// enfoque recursivo para la función conocida reverse para invertir una cadena

void reverse(char s[], int left, int right) { 
    void swap(char [], int, int);

    if (left >= right) {
        return;
    }
    
    swap(s, left, right);
    reverse(s, left+1, right-1);
}

void swap(char s[], int i, int j) {
    int _temp;

    _temp = s[i];
    s[i] = s[j];
    s[j] = _temp;
}

int main() {
    char s[] = "oluclac raborpa a av zeugirdoR ogaireP nauJ egroJ";
    reverse(s, 0, strlen(s)-1);
    printf("%s", s);
    return 0;
}