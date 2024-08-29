# include <stdio.h>
# include <time.h>
# include <stdlib.h>

# define DECK_SIZE 52
# define HAND_SIZE 7

// enumerated variable for storing the suit values
typedef enum {Clubs, Diamonds, Hearts, Spades} Suit;

// struct for representing a single card
typedef struct {
    Suit s_val;
    short p_val;
} Card;

// functions that we will be using
void initialize_deck(Card[]);
void random_shuffle(Card[]);
char *get_suit(Card);
void print_deck(Card[]);
void generate_hand(int, Card[], int[]);
void evaluate_hand(Card[], int[]);

// function for initializing a deck in an ordered way
void initialize_deck(Card array[]) {
    int i = 0, suit, pips;
    for (suit = Clubs; suit <= Spades; suit++) {
        for (pips = 1; pips <= 13; pips++) {
            array[i].s_val = (Suit) suit;   // casting necessary
            array[i++].p_val = pips;
        }
    }
}

// function that randomly shuffles the deck using an algorithm for random allocation
void random_shuffle(Card array[]) {
    int i;

    for (i = 0; i < DECK_SIZE; i++) {
        int j = i + (rand() % (DECK_SIZE-i));  // generate a random index in the range [i, 51]
        Card temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

// function for getting the suit value of a card in form of a string
char * get_suit(Card card) {
    char *names[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};

    return names[card.s_val];
}

// function for printing a deck
void print_deck(Card deck[]) {
    for (int i = 0; i < DECK_SIZE; i++) {
        printf("%d. %d of %s\n", i+1, deck[i].p_val, get_suit(deck[i]));
    }
}

// function for generating one 7-card hand and evaluating it (pair, two pairs, 3 of a kind, full house or 4 of a kind)
void generate_hand(int hand_size, Card deck[], int results[]) {
    Card hand[hand_size];

    for (int i = 0; i < hand_size; i++) {
        hand[i] = deck[i];
    }

    evaluate_hand(hand, results);
}

// function for evaluating the results of a single hand and updating the results array
void evaluate_hand(Card hand[], int results[]) {
    int counts[14] = {0};   // counts[i] stores the number of cards with a pips value = i
    int pairs = 0;
    int three_of_a_kind = 0;
    int four_of_a_kind = 0;

    for (int i = 0; i < 7; i++) {
        counts[hand[i].p_val]++;
    }

    for (int i = 1; i <= 13; i++) {
        if (counts[i] == 2)
            pairs++;
        else if (counts[i] == 3)
            three_of_a_kind++;
        else if (counts[i] == 4)
            four_of_a_kind++;
    }

    if (three_of_a_kind==1 && pairs==1)     // important to evaluate full first (if not, it would be counted as a pair or a trio)
        results[3]++;
    else if (pairs==1)
        results[0]++;
    else if (pairs==2)
        results[1]++;
    else if (three_of_a_kind==1)
        results[2]++;
    else if (four_of_a_kind==1)
        results[4]++;
    
}

int main(void) {
    // we declare an array of Cards for representing the deck of 52 cards
    Card deck[52];
    int number_simulations = 1000000;
    int results[5] = {0};   // array for counting the number of pairs, two pairs, 3 of a kind, full house and 4 of a kind

    srand(time(NULL));
    for (int i = 0; i < number_simulations; i++) {
        initialize_deck(deck);
        random_shuffle(deck);   // shuffle the deck
        generate_hand(HAND_SIZE, deck, results);     // evaluation is implicit in this function
    }

    // we have fullfilled the results array with 1000000 simulations. Now, we get the probabilities
    char *names[5] = {"pair", "two pairs", "three of a kind", "full house", "four of a kind"};
    int sum = 0;
    for (int i=0; i<5; i++) {
        printf("Probability of %s = %lf\n", names[i], (double) results[i]/number_simulations);
    }
    // the probabilities shown are an aproximation of the values in the table 
    
}