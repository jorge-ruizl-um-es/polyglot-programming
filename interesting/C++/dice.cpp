// this program computes the probabilities 
// for each posible result when throwing two dices

# include <iostream>
# include <cstdlib>
# include <ctime>
using namespace std;

const int sides = 6;
inline int rand_side() {return (rand() % sides + 1);}

int main() {
    const int n_dice = 2;

    srand(clock());
    cout << "\nEnter number of trials: ";
    int trials;
    cin >> trials;
    int* outcomes = new int[n_dice*sides + 1](); // outcomes[0] and outcomes[1] will always be 0
    // parenthesis are used to initialize to 0

    for (int i = 0; i < trials; i++) {
        int total_dice = 0;
        for (int j = 0; j < n_dice; j++) {
                int die_number = rand_side();
                total_dice  += die_number;
        }
        outcomes[total_dice]++;
    }
    cout << "\nProbabilities:\n";
    for (int j=2; j < n_dice*sides + 1; j++) {
        cout << "Number: " << j << "Probability: "
            << static_cast<double>(outcomes[j])/trials << endl;     // converts outcomes[j] for doing a double division
    }

    delete[] outcomes;      // free memory
    return 0;
}