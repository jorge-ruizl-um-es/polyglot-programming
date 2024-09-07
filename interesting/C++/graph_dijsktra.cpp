# include <iostream>
# include <ctime>
# include <cstdlib>
# include <vector>
# include <string>
# include <algorithm>
# include <limits>

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

// functions for getting random values
inline double prob(void) {return static_cast<double>(rand()) / RAND_MAX;}
inline double dist(double min, double max) {return min + static_cast<double>(rand()) / RAND_MAX * (max-min); }

// implementation of the Graph --> I choose a representation as an Adjacency Matrix because we will be working 
// with graphs with at least 50 nodes.
class Graph {
    public:
        // constructor. Creates an empty graph with a given number of nodes
        Graph(int nodes, int edges = 0): nodes(nodes), edges(edges) {

            // we create a graph as a double matrix VERTICESxVERTICES --> if the position (i,j) is -1, then nodes i and j aren't connected
            // we initialize every position matrix[i][j] = -1, and then, we will be adding edges
            // if there is an edge between i and j, then matrix[i][j] will be equal to the distance of the edge
            // it won't be posible to add nodes (it would require to resize the matrix)

            matrix = new double*[nodes];    // columns
            // this is an initialization in memory, the declaration is already done y private
    
            for (int i = 0; i < nodes; i++) {
                matrix[i] = new double[nodes];  // rows
                for (int j = 0; j < nodes; j++) {
                    matrix[i][j] = -1.0;
                }
            }
            node_values.resize(nodes);     // initialize all the node values at 0
        }

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
        void set_node_value(int i, string a) {node_values[i] = a;}
        void set_edge_value(int i, int j, double a) {matrix[i][j] = a;}

        // declaration of methods for working with the Graph:
        bool adjacent(int i, int j);
        vector<int> neighbors(int i);
        void add_Edge(int from, int to, double dist);
        void delete_Edge(int from, int to); 
        void build_random_graph(double density, double min_dist, double max_dist);   

        // operator overload for printing a Graph:
        friend ostream& operator<< (ostream& out, const Graph& g);

    private:
        int nodes, edges;
        double** matrix;
        vector<string> node_values;  
};

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
void Graph::add_Edge(int from, int to, double dist) {
    if (from < 0 || to < 0 || from >= nodes || to >= nodes) {
        exit(0);
    }
    else if (matrix[from][to] != -1.0 || matrix[to][from] != -1.0) {     // the edges are undirected (matrix[i][j] == matrix[j][i])
        exit(0);
    }
    matrix[from][to] = matrix[to][from] = dist;
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
        edges--;
    }
}

// method for building a random graph of VERTICES nodes
void Graph::build_random_graph(double density, double min_dist, double max_dist) {
    for (int i = 0; i < nodes; ++i) {
        for (int j = i; j < nodes; ++j) {
            if (i!=j && prob() < density)   // no loops 
                add_Edge(i, j, dist(min_dist, max_dist));     
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

// ######################################### SHORTEST PATH - DIJKSTRA'S ALGORITHM ####################################

class ShortestPath {
    public: 
        // constructor
        ShortestPath(Graph& graph): graph(graph) {}

        vector<int> path(int u, int w);
        double path_size(int u, int w);
        double average_path_len(int source);

    private:
        Graph& graph;
        vector<double> dijkstra(int source, vector<int>& parent);
};

// method for running Dijsktra from a source node --> algorithm per se
vector<double> ShortestPath::dijkstra(int source, vector<int>& parent) {
    int n = graph.V();
    vector<double> dist(n, numeric_limits<double>::infinity());
    PriorityQueue pq;

    dist[source] = 0;
    pq.insert(source, 0);
    parent[source] = -1;    // centinel --> points to the parent of source, which is none (represented by -1)

    while (!pq.is_empty()) {
        int u = pq.minPriority().element;
        for (int v : graph.neighbors(u)) {
            double weight =  graph.get_edge_value(u, v);
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.insert(v, dist[v]);
                parent[v] = u;
            }
        }
    }
    return dist;     // vector of minimun distances from source to each node i, with i between 0 and n
}

// uses dijstra to find the shortest path between u and w
vector<int> ShortestPath::path(int u, int w) {
    vector<int> parent(graph.V());  // vector of parents of each node
    dijkstra(u, parent);       // build vector of parents
    vector<int> path; 

    for (int v = w; v != -1; v = parent[v]) {      // starts from w and reaches source (u) using the parents' vector built with dijkstra
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;

}

// uses dijkstra to get shortest path size between u and w
double ShortestPath::path_size(int u, int w) {
    vector<int> parent(graph.V());  // vector of parents of each node
    vector<double> distances = dijkstra(u, parent);
    return distances[w];
}

// computes the minimum distances from source to each node of a graph, and gets the average
double ShortestPath::average_path_len(int source) {
    vector<int> parent(graph.V());
    vector<double> distances = dijkstra(source, parent);
    double total_dist = 0;
    int count = 0;
    
    for (int i=0; i < distances.size(); i++) {
        if (distances[i] < numeric_limits<double>::infinity()) {
            total_dist += distances[i];
            ++count;
        }
    }

    return total_dist/count; 
}

// ---------------------------------------------- MAIN PROGRAM AND FUNCTIONS ------------------------------------

// function for calculating the average path lenght of n graphs built randomly, each with the same number of nodes 
double simulate_path_len(int n_graph, int n_nodes, double den, double min_d, double max_d) {
    double total_avg_lenght = 0.0;

    for (int i = 0; i < n_graph; i++) {
        Graph g(n_nodes);
        g.build_random_graph(den, min_d, max_d);
        ShortestPath algorithm(g);
        total_avg_lenght += algorithm.average_path_len(0);  // apply dijkstra from node 0 to each other node
    }

    return total_avg_lenght/n_graph;
}

int main() {
    srand(time(0));
    int num_graphs = 3;
    double avg_lenght = simulate_path_len(num_graphs, VERTICES, DENSITY, MIN_DIST, MAX_DIST);
    std::cout << "Average path lenght over " << num_graphs << " graphs is: " << avg_lenght << endl;
    return 0;
}