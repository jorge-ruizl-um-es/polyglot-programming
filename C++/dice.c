/* this program computes the probabilities 
for each posible result when throwing two dices */

# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# define SIDES 6
# define RAND_SIDE (rand() % SIDES + 1)

int main() {
    int trials, d1, d2;
    int outcomes[13] = {0}; // outcomes[0] and outcomes[1] will always be 0
    int i, j;

    srand(time(NULL));
    printf("\nEnter number of trials: ");
    scanf("%d", &trials);
    for (i = 0; i < trials; i++) {
        outcomes[(d1=RAND_SIDE) + (d2=RAND_SIDE)]++;
    }
    printf("\nProbabilities:\n");
    for (j=2; j<13; j++) {
        printf("Number: %d \t Probability: %.3lf\n", j, (double) outcomes[j] / trials);
    }
    return 0;
}