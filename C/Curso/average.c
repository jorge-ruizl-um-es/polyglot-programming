# include <stdio.h>
# include <stdlib.h>

# define MAX_LEN 100000

// function to calculate the average of the integers in an array
double get_average(int array[], int size) {
    // variables for getting the average weight
    int sum = 0;

    for (int i = 0; i < size; i++) {
        sum += array[i]; 
    }
    return (sum/size);
}

int main(void) {
    // variables for reading the data
    FILE *file;
    int weights[MAX_LEN];
    int count = 0;
    char data[] = "elephant_seal_data.txt";

    // variable to store the average
    double average;

    // we have to read the file into our array "weights"
    file = fopen(data, "r");
    
    while (fscanf(file, "%d", &weights[count]) == 1) {
        count++;
        if (count >= MAX_LEN) {
            printf("Error");
            break;
        }
    }

    fclose(file);

    // then, we call the function to get the average
    average = get_average(weights, count);
    printf("The average weight of the northern elephant seal is: %lf\n", average);

}