# include <iostream>
# include <ctime>
# include <cstdlib>
# include <vector>
# include <string>
# include <algorithm>
# include <limits>
#include <fstream>

using namespace std;

// .......................................... PRIORITY QUEUE IMPLEMENTATION ........................................
struct pqueuenode {
    int element;
    double priority;

    // This is necessary for the correct working of minPriority
    bool operator==(const pqueuenode& other) const {
        return element == other.element && priority == other.priority;
    }
};

class PriorityQueue {
public:
    PriorityQueue();
    
    // required methods
    void chgPriority(int element, double priority);
    pqueuenode minPriority();
    bool contains(int element);
    bool is_empty();
    void insert(int element, double priority);
    int top() const;
    int size() const;

    friend ostream& operator << (ostream& out, PriorityQueue& pq);

private:
    std::vector<pqueuenode> queue; // Vector of pairs (element, priority)

    pqueuenode search_min(void) const;
};

PriorityQueue::PriorityQueue() {}

void PriorityQueue::chgPriority(int element, double new_priority) {
    for (int i = 0; i < queue.size(); i++) {
        if (queue[i].element == element) {
            queue[i].priority = new_priority;
            break;
        }
    }
}

pqueuenode PriorityQueue::search_min(void) const {
    if (queue.empty()) {
        throw std::runtime_error("PriorityQueue is empty");
    }

    double min_prior = numeric_limits<double>::infinity();
    pqueuenode min;

    for (int i = 0; i < queue.size(); i++) {
        if (queue[i].priority < min_prior) {
            min_prior = queue[i].priority;
            min = queue[i];
        }
    }

    return min;
}

pqueuenode PriorityQueue::minPriority(void) {
    if (queue.empty()) {
        throw std::runtime_error("PriorityQueue is empty");
    }

    pqueuenode min_prior = search_min();
    for (auto it = queue.begin(); it != queue.end(); ++it) {
        if (*it == min_prior) {
            queue.erase(it);
            break;
        }
    }
    return min_prior;
}

bool PriorityQueue::contains(int element) {
    bool out = false;
    for (int i = 0; i<queue.size(); i++) {
        if (queue[i].element == element) {
            out = true;
            break;
        }
    }
    return out;
}

bool PriorityQueue::is_empty() {
    return queue.empty();
}

void PriorityQueue::insert(int element, double priority) {
    if (contains(element)==true) {
        chgPriority(element, priority);
    }
    else {
    queue.push_back(pqueuenode{element, priority});
    }
}

int PriorityQueue::top() const {
    return search_min().element;
}

int PriorityQueue::size() const {
    return queue.size();
}

ostream& operator << (ostream& out, PriorityQueue& pq) {
    for (int i = 0; i < pq.size(); i++) {
        out << "( "<< pq.queue[i].element << ", " << pq.queue[i].priority <<  " )";
    }
    out << endl;
    return out;
}


// ----------------------------------------- GRAPH IMPLEMENTATION ---------------------------------------------

// constants that we will be using
const int VERTICES = 50;
const double DENSITY = 0.4;
const double MIN_DIST = 1.0;
const double MAX_DIST = 10.0;

// color definition
enum class Color {RED, GREEN, BLUE, NONE};  // (NONE for no edge)

// overloading for printing a color
ostream& operator<<(ostream& out, Color c) {
    switch(c) {
        case Color::RED:
            out << "Red";
            break;
        case Color::GREEN:
            out << "Green";
            break;
        case Color::BLUE:
            out << "Blue";
            break;
        case Color::NONE:
            out << "None";
            break;
    }
    return out;
}

// functions for getting random values
inline double prob(void) {return static_cast<double>(rand()) / RAND_MAX;}
inline double dist(double min, double max) {return min + static_cast<double>(rand()) / RAND_MAX * (max-min); }
inline Color random_color(void) { return static_cast<Color> (rand() % 3); }


// implementation of the Graph --> I choose a representation as an Adjacency Matrix because we will be working 
// with graphs with at least 50 nodes. It only builds undirected graphs default
class Graph {
    public:
        // constructor. Creates an empty graph with a given number of nodes
        Graph(int nodes, int edges = 0): nodes(nodes), edges(edges) {

            // we create a graph as a double matrix VERTICESxVERTICES --> if the position (i,j) is -1, then nodes i and j aren't connected
            // we initialize every position matrix[i][j] = -1, and then, we will be adding edges
            // if there is an edge between i and j, then matrix[i][j] will be equal to the distance of the edge
            // it won't be posible to add nodes (it would require to resize the matrix)

            matrix = new double*[nodes];    // columns
    
            for (int i = 0; i < nodes; i++) {
                matrix[i] = new double[nodes];  // rows
                for (int j = 0; j < nodes; j++) {
                    matrix[i][j] = -1.0;
                }
            }
            node_values.resize(nodes);     // initialize all the node values at 0
        }

        // constructor for reading a Graph from a file
        Graph(const std::string& filename);

        // destructor (delete)
        ~Graph() {
            for (int i = 0; i < nodes; i++)
                delete[] matrix[i];
            delete [] matrix;
        }

        // get and set operations
        int V(void) {return nodes;}
        int E(void) {return edges;}
        string get_node_value(int i) {return node_values[i];}
        double get_edge_value(int i, int j) {return matrix[i][j];}
        Color get_edge_color(int i, int j) {return color_matrix[i][j];}
        void set_node_value(int i, string a) {node_values[i] = a;}
        void set_edge_value(int i, int j, double a) {matrix[i][j] = a;}

        // declaration of methods for working with the Graph:
        bool adjacent(int i, int j);
        vector<int> neighbors(int i);
        void add_Edge(int from, int to, double dist, Color c);
        void delete_Edge(int from, int to); 
        void build_random_graph(double density, double min_dist, double max_dist);   
        void print_color(void);

        // operator overload for printing a Graph:
        friend ostream& operator<< (ostream& out, const Graph& g);

    private:
        int nodes, edges;
        double** matrix;
        Color** color_matrix;
        vector<string> node_values;  
};

// constructor for reading from a file and assign colors randomly
Graph::Graph(const std::string& filename) {
    ifstream infile(filename);

    infile >> nodes;    // read number of nodes
    edges = 0;

    // initialize matrix and color_matrix
    matrix = new double*[nodes];
    color_matrix = new Color*[nodes];
    for (int i=0; i < nodes; i++) {
        matrix[i] = new double[nodes];
        color_matrix[i] = new Color[nodes];
        for (int j=0; j < nodes; j++) {
            matrix[i][j] = -1.0;    // no edge for the moment
            color_matrix[i][j] = Color::NONE;   // no color for the moment
        }
    }
    node_values.resize(nodes);

    int i, j;
    double k;

    // read each line from file
    while (infile >> i >> j >> k) {
        if (i < 0 || j < 0 || i>=nodes || j>=nodes || k<0)
            throw std::runtime_error("Índice de nodo fuera de rango");
        if (matrix[i][j] == -1.0) {
            add_Edge(i,j,k, random_color());
        }
    }

    infile.close();
}

// method for checking if nodes i and j are adjacent
bool Graph::adjacent(int i, int j) {
    return matrix[i][j] != -1;
}

// method for getting a list of adjacent nodes to i
vector<int> Graph::neighbors(int i) {
    vector<int> result;

    if (i < nodes) {
        for (int j=0; j<nodes; j++) {
            if (matrix[i][j] != -1) {
                result.push_back(j);
            }
        }
    }
    return result;
}

// method for adding edges in a more efficient way
void Graph::add_Edge(int from, int to, double dist, Color c) {
    if (from < 0 || to < 0 || from >= nodes || to >= nodes) {
        exit(0);
    }
    else if (matrix[from][to] != -1.0 || matrix[to][from] != -1.0) {     // the edges are undirected (matrix[i][j] == matrix[j][i])
        exit(0);
    }
    matrix[from][to] = matrix[to][from] = dist;
    color_matrix[from][to] = color_matrix[to][from] = c;
    edges++;
}

// method for removing edges
void Graph::delete_Edge(int from, int to) {
    if (from < 0 || to < 0 || from >= nodes || to >= nodes) {
        exit(0);
    }
    else if (matrix[from][to] != -1.0 || matrix[to][from] != -1.0) {     // the edges are undirected (matrix[i][j] == matrix[j][i])
        exit(0);
    }
    if (matrix[from][to] != -1) {
        matrix[from][to] = matrix[to][from] = -1;
        color_matrix[from][to] = color_matrix[to][from] = Color::NONE;
        edges--;
    }
}

// method for building a random graph of VERTICES nodes
void Graph::build_random_graph(double density, double min_dist, double max_dist) {
    for (int i = 0; i < nodes; ++i) {
        for (int j = i; j < nodes; ++j) {
            if (i!=j && prob() < density)   // no loops 
                add_Edge(i, j, dist(min_dist, max_dist), random_color());     
        }
    }
}

// operator overloading for giving an output of a Graph:
// I've programmed this for debugging
ostream& operator<< (ostream& out, const Graph& g) {
    for (int i = 0; i < g.nodes; i++) {
        for (int j = 0; j < g.nodes; j++) {
            out << g.matrix[i][j] << "  ";
        }
        out << endl;
    }
    out << endl;
    return out;
}

//  print color matrix (depuration)
void Graph::print_color(void) {
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            cout << color_matrix[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

// -------------------------------------------------- PRIM ALGORITHM --------------------------------------------

struct edge {
    int v1;
    int v2;
};

class PrimAlgorithm {
    public:
        PrimAlgorithm(Graph& graph);
        double generateMST(int source, vector<edge>& tree, Color c);
    
    private:
        Graph& graph;
        vector<double> dist;    // vector with the minimum dist from source to each node
        vector<int> edges;      // vector with the nearest node of each node
        vector<int> MST;        // vector with the nodes that have already been evaluated
        PriorityQueue U;   // queue with the nodes that are reachable in each moment and their costs
};

// constructor
PrimAlgorithm::PrimAlgorithm(Graph& graph): graph(graph), dist(graph.V(), numeric_limits<double>::infinity()), edges(graph.V(), -1) {}

// algorithm implementation
// ADDITION: we add a Color c in order to specificate a MST built with edges of a single color. It is optional,
// so if you don't want to distinguish, it will assume color = NONE and make no distinction.
double PrimAlgorithm::generateMST(int source, vector<edge>& tree, Color c = Color::NONE) {    // the algorithm will build the vector of edges
    int startvertex = source;
    double cost = 0.0;
    dist[startvertex] = 0.0;
    U.insert(startvertex, 0.0);

    while(MST.size() != graph.V()) {   
        if (U.is_empty()) {
            return -1;      // the graph is disjointed
        }
        pqueuenode node = U.minPriority();

        int u = node.element; // less wighted node
        cost += node.priority;  // add the cost of adding the node to the tree
        if (c == Color::NONE || graph.get_edge_color(u, edges[u]) == c) {
            MST.push_back(u);   // add to closed

            if (edges[u] != -1) {
                edge new_edge{edges[u], u};
                tree.push_back(new_edge);
            }
        

            // proccesses all the adjacent nodes to u
            for (int v : graph.neighbors(u)) {   // using iterators (feature in for statements in C++)
                double weight = graph.get_edge_value(u, v);

                // if v not in MST and weight is less than dist[v]
                if (find(MST.begin(), MST.end(), v) == MST.end() && weight < dist[v]) {
                    dist[v] = weight;
                    edges[v] = u;
                    U.insert(v, dist[v]);
                }
            }
        }
    }
    return cost;
}

// main program
int main() {
    Graph graph("graph.txt");
    PrimAlgorithm algo(graph);

    vector<edge> tree;
    double cost = algo.generateMST(0, tree);    // allows to specify a color
    cout << "The cost of the MST is " << cost << endl;
    if (cost != -1) {
        cout << "The sequence of edges added to the tree is: " << endl;
        for (int i = 0; i < tree.size(); i++) {
            int v1 = tree[i].v1;
            int v2 = tree[i].v2;
            cout << "(" << v1 << ", " << v2 << ")" << endl;
        }
    }
    else {
        cout << "The graph is disjointed" << endl;
    }
}
