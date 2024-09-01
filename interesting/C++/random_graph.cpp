# include <iostream>
# include <cstdlib>
# include <ctime>
using namespace std;

const int SIZE = 7;
const double density = 0.19;

double prob(void) {     // returns a random probability between 0 and 1
    return static_cast<double>(rand()) / RAND_MAX;
}

int main() {
    bool** graph;       // bidimensional array of bool
    srand(time(0));     // seed for rand()

    // we create a graph as a bool matrix 7x7 --> if the position (i, j) is TRUE, then vertices i and j are conected
    graph = new bool*[SIZE];    // columns
    
    for (int i = 0; i < SIZE; i++) {
        graph[i] = new bool[SIZE];  // rows
    }

    // put edges randomly according to density (probability that edges exist)
    for (int i = 0; i < SIZE; ++i) {
        for (int j = i; j < SIZE; ++j) {
            if (i==j)
                graph[i][j] = false;    // no loops 
            else
                graph[i][j] = graph[j][i] = (prob() < density);     // undirected graph
        }
    }

    delete[] graph;     // free the memory used
    return 0;
}
