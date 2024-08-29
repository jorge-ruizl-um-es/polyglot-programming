# include <stdio.h>
# include <stdlib.h>

# define MAXLEN 1000    // max lenght of the array
# define FILENAME "file.txt"

// struct for the tree
typedef struct element {
    int data;
    struct element *left;
    struct element *right;
} Node;

// functions
int read_first_size(FILE *);
void read_array(FILE *, int[], int);
Node *array_to_tree(int[], int, int);
void print_inorder(Node *);
Node *create_node(void);
Node *init_node(int, Node*, Node*);

// function to get the size (number of elements to read)
int read_first_size(FILE *pf) {
    int size;

    if (fscanf(pf, "%d", &size) == 1)
        return size;
    else
        return -1;
}

// function to store in the array the numbers that are indicated by size
void read_array(FILE *pf, int data[], int size) {
    int i = 0;
    while ((fscanf(pf, "%d", &data[i]) == 1) && i < size)
        i++;
}

// functions for dealing with trees

void print_inorder(Node *root) {
    if (root != NULL) {
        print_inorder(root->left);
        printf("%d\t", root->data);
        print_inorder(root->right);
    }
}

Node *create_node(void) {
    return (Node *)malloc(sizeof(Node));
}

Node *init_node(int d, Node *left, Node *right) {
    Node *new_node = create_node();
    new_node->data = d;
    new_node->left = left;
    new_node->right = right;
    return new_node;
}

Node *array_to_tree(int array[], int i, int size) {
    if (i>=size)
        return NULL;
    else
        return (init_node(array[i], array_to_tree(array, 2*i+1, size), array_to_tree(array, 2*i+2, size)));
}

// main routine
int main() {
    FILE *pf;
    int data[MAXLEN];

    pf = fopen(FILENAME, "r");

    int size = read_first_size(pf);
    read_array(pf, data, size);
    fclose(pf);

    Node *root = array_to_tree(data, 0, size);

    print_inorder(root);
    return 0;
}