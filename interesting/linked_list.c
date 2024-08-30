# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
#include <assert.h>

typedef struct list {
    int data;
    struct list *next; 
} list;

int is_empty(list *head) {
    return head==NULL;
}

list *create_node(int d) {
    list *head = malloc(sizeof(list));
    head->data = d;
    head->next = NULL;
    return head;
}

list *add_to_front(int d, list *l) {
    list *head = create_node(d);
    head->next = l;
    return head;
} 

list *array_to_list(int array[], int size) {
    list *head = create_node(array[size-1]);
    for (int i = size-2; i>=0; i--) {
        head = add_to_front(array[i], head);
    }
}

void print_list_rec (list *head) {
    if (head == NULL)
        ;
    else {
        printf("%d : ", head->data);
        print_list_rec(head->next);
    }
}

void concat(list *h1, list *h2) {
    assert (h1 != NULL);    // abbort if h1 is NULL
    if (h1->next == NULL)
        h1->next = h2;
    else 
        concat(h1->next, h2);
}

void concat2(list **h1, list *h2) {
    if (*h1==NULL) {
        *h1 = h2;       // we're modifying h1
    }
    else {
        while ((*h1)->next != NULL)
            *h1 = (*h1)->next;
        (*h1)->next = h2;
    }
}

int main() {
    list *head1 = NULL;
    list *head2 = NULL;
    int data2[3] = {11, 17, 21};
    head2 = array_to_list(data2, 3);
    concat2(&head1, head2);     // ojo!! para concat2 hay que llamar por referencia!!!
    print_list_rec(head1);
    return 0;
}