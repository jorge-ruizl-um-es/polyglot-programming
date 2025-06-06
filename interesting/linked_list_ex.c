# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# define NUM_MAX 50   // the random integers will be generated between 0 and NUM_MAX-1
# define COLUMNS 5
# define NUM_OF_INTS 200

// we define the appropriate struct for building a linked list
typedef struct list {
    int data;
    struct list *next;
    struct list *previous;  // for double link
} list;

// --------------------------------------------------------------------------------------
// functions that we will be using
list *create_node(int);
list *add_to_front(int, list *);
list *initialize_list(int);
void print_list(list *);

// functions for the first way of doing the exercise
void swap(list *, list *);
void bubble_sort(list *head);
void remove_adjacent(list *);

// functions for the second way
void delete_element(list *);
void search_elements(list *);

// ---------------------------------------------------------------------------------------

// function that creates a node that stores an integer
list *create_node(int d) {
    list *head = malloc(sizeof(list));
    head->data = d;
    head->next = NULL;
    head->previous = NULL;
    return head;
}

// function that adds a new element in the front of the list
list *add_to_front(int d, list *head) {
    list *h = create_node(d);
    head->previous = h;
    h->next = head;
    return h;
}

// function that stores a randomly generated set of 100 integers in a list (each integer in a position of it)
list *initialize_list(int rep) {
    list *head = create_node(rand() % NUM_MAX);
    for (int i=0; i<rep-1; i++) {
        head = add_to_front(rand() % NUM_MAX, head);
    }
    return head;
}

// function for printing the list in rows of 5 numbers
void print_list(list *head) {
    int count = 0;
    while (head != NULL) {
        printf("%3d :", head->data);
        count++;
        if (count % 5 == 0) {
            printf("\n");
        }
        head = head->next;
    }
}

// FIRST WAY -----------------------------------------

// functions that sorts a linked list with bubble sort algorithm
void swap(list *a, list *b) {
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void bubble_sort(list *head) {
    if (head==NULL)
        return;

    list *end = NULL;
    int swapped;

    do {
        list *current = head;
        swapped = 0;

        while (current->next != end) {
            if (current->data > current->next->data) {
                swap(current, current->next);
                swapped = 1;
            }
            current = current->next;
        }

        end = current;  // reduces list size in each iteration
    } while (swapped);
}

// once you've sorted the list, we delete adjacent nodes that contains the same number
void remove_adjacent(list *head) {
    list *current = head;
    list *nextNode;

    while (current->next != NULL) {
        nextNode = current->next;

        if (current->data == nextNode->data) {
            current->next = nextNode->next;
            if (nextNode->next != NULL)
                nextNode->next->previous = current;
            free(nextNode);     // we delete nextNode
        }
        else
            current = current->next;
    }
} 

// SECOND WAY -----------------------------------------------------
void delete_element(list *element) {
    if (element==NULL) 
        return;
    list *nextNode = element->next;
    list *prevNode = element->previous;

    if (prevNode != NULL)
        prevNode->next = nextNode;
    if (nextNode != NULL)
        nextNode->previous = prevNode;
    free(element);
}

void search_elements(list *head) {      // done in a recursive way
    if (head == NULL || head->next == NULL)
        return;

    else {
        int data = head->data;
        list *current = head->next;
        while (current != NULL) {
            list *nextCurrent = current->next;
            if (current->data == data) {
                delete_element(current);
            }
            current = nextCurrent;
        }
        search_elements(head->next);
    }
}

// main routine
int main(void) {
    srand(time(NULL));

    list *head = initialize_list(NUM_OF_INTS);
    printf("\nThe unsorted randomly generated list is:\n");
    print_list(head);
    printf("\n\n");

    // FIRST WAY --> sort the list and remove adjacent duplicates
    printf("The sorted list is:\n");    
    bubble_sort(head);
    print_list(head);
    printf("\n\n");
    printf("The sorted list without duplicates is:\n");
    remove_adjacent(head);
    print_list(head);
    printf("\n\n");

    // SECOND WAY --> set a position of the list, and iterate through it while removing the elements with the same number
    printf("\nThe list without duplicates is (no previous sorting):\n");
    search_elements(head);
    print_list(head);
}