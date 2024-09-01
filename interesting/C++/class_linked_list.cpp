# include <iostream>
using namespace std;

struct slistelem {      // subclase node de la lista, no necesita constructor
    char data;
    slistelem* next;
};

class slist{
    public:
        slist(): h(0){}     // initialize an empty list --> head points to 0, which is the null pointer
        ~slist();   // destructor (declaration)

        void prepend(char c);      // declaration of the method
        friend ostream& operator<< (ostream& out, const slist& list);

    private:
        slistelem* h;   // head of the list (first element)

        void release(void) {
            slistelem* current = h;
            while (current != 0) {
                slistelem* next = current->next;
                delete current;
                current = next;
            }
            h = nullptr;
        }
};

void slist::prepend (char c) {
    slistelem* temp = new slistelem;
    temp->next = h;
    temp->data = c;
    h = temp;
}

slist::~slist() {
    cout << "destructor called" << endl;
    release();
}

ostream& operator<< (ostream& out, const slist& list) {
    slistelem* current = list.h;
    while (current != 0) {
        out << current->data << " ";
        current = current->next;
    }
    out << endl;
    return out; 
}

int main() {
    slist list;
    list.prepend('a');
    list.prepend('b');
    list.prepend('c');
    cout << list;
    cout << "Finish building list\n";
    return 0;
}