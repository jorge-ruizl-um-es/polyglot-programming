# include <stdio.h>
# include <stdlib.h>

# define FILENAME "file.txt"
# define MAXLEN 1000

// program for reading a set of pairs of numbers from a file, storing the first digit as the size of the set,
// and creating an array of unids of a struct containg two numbers: numerator and denominator

typedef struct {
    int numerator;
    int denominator;
} Rational;

// functions
void read_file(FILE*, int[], int*);
void rational_array(int[], Rational[], int);
Rational add(Rational, Rational);
Rational subs(Rational, Rational);
Rational mult(Rational, Rational);
Rational division(Rational, Rational);

// function for reading a file into an array of ints and storing the size
void read_file(FILE *fp, int array[], int *size) {
    int i = 0;

    while (fscanf(fp, "%d", &array[i]) == 1 && i < MAXLEN) {
        i++;
    }

    if (i>0)    // if something has been read
        *(size) = array[0];
}

// function for creating a new array of Rationals from the array that has been read
void rational_array(int input[], Rational output[], int size) {
    int i, j=0;

    for (i=1; i<size*2; i+=2) {
        int numerator = input[i];
        int denominator = input[i+1];

        Rational fraction = {numerator, denominator};
        output[j++] = fraction;
    }
}

// basic operations
Rational add(Rational r1, Rational r2) {
    Rational out;
    out.denominator = r1.denominator * r2.denominator;
    out.numerator = r1.numerator*r2.denominator + r2.numerator*r1.denominator;
    return out;
}

Rational subs(Rational r1, Rational r2) {
    Rational out;
    out.denominator = r1.denominator * r2.denominator;
    out.numerator = r1.numerator*r2.denominator - r2.numerator*r1.denominator;
    return out;
}

Rational mult(Rational r1, Rational r2) {
    Rational out;
    out.denominator = r1.denominator * r2.denominator;
    out.numerator = r1.numerator*r2.numerator;
    return out;
}

Rational division(Rational r1, Rational r2) {
    Rational out;
    out.denominator = r1.denominator * r2.numerator;
    out.numerator = r1.numerator*r2.denominator;
    return out;
}

// main function
int main() {
    FILE *fp;
    int size, data[MAXLEN];

    // reading the file
    fp = fopen(FILENAME, "r");
    read_file(fp, data, &size);
    fclose(fp);

    // creating the rational numbers' array
    Rational out_data[size], sum = {0, 1};
    rational_array(data, out_data, size);

    printf("The stored rational numbers are:\n");
    for (int i = 0; i < size; i++) {
        printf("%d/%d\n", out_data[i].numerator, out_data[i].denominator);
        sum = add(sum, out_data[i]);
    }
    printf("The sum of the rationals is: %d/%d\n", sum.numerator, sum.denominator);

    Rational rsize = {size, 1};
    Rational average = division(sum, rsize);
    printf("The average of the rationals is %d/%d\n", average.numerator, average.denominator);

}
