# include <iostream>
using namespace std;

class list_element{
    public:
        list_element(int n = 0, list_element* ptr=0): d(n), next(ptr) {}
        int d;
        list_element* next;
};

class list {
    public:
        // constructors
        list(): head(nullptr), cursor(nullptr) {}       // nullptr and 0 are equivalent
        // podriamos incluir un constructor que tomara un array y su tamaño, y lo convirtiera en una lista:
        list(const int* arr, int n): head(nullptr), cursor(nullptr) {
            cursor = head = new list_element(arr[0], head);
            for (int i = 1; i < n; i++) {
                head = new list_element(arr[i], head);
            }
        }

        // destructors
        ~list();
        void prepend(int n);    // insert n value at the front of the list
        int get_element() {return cursor->d;}
        void advance() {cursor = cursor->next;}
        void print();

    private:
        list_element* head;
        list_element* cursor;
};

void list::prepend(int n) {
    if (head == 0) {
        // empty case --> create the list (properly initialize head and cursor)
        cursor = head = new list_element(n, head);  // we can do this because of the constructor in list_element
    }
    else {
        head = new list_element(n, head);
    }
}

void list::print() {
    list_element* h = head;

    while (h!=nullptr) {
        cout << h->d << ", ";
        h = h->next;
    }
    cout << "###" << endl;
}

// destructor
list::~list() {
    for (cursor = head; cursor!=0;) {
        cursor = head->next;
        delete head;
        head = cursor;
    }
}

int main() {
    int array[4] = {1, 2, 3, 4};
    list list_from_arr(array, 4);
    list_from_arr.print();
}