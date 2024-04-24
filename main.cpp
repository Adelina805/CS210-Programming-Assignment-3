#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int VERTEXCOUNT = 5;

// Node Class: Nodes for Binary Heap
template<typename T>
class Node {
private:
    T *data;
    Node<T> *leftChild;
    Node<T> *rightChild;
    Node<T> *parent;

public:
    // Constructor
    Node(T *data) {
        this->data = data;
        leftChild = nullptr;
        rightChild = nullptr;
        parent = nullptr;
    }

    // Destructor
    ~Node() {
        delete data;
        data = nullptr;
    }

    // Getters
    T* getData() const {
        return data;
    }
    Node<T>* getLeftChild() const {
        return leftChild;
    }
    Node<T>* getRightChild() const {
        return rightChild;
    }
    Node<T>* getParent() const {
        return parent;
    }

    // Setters
    void setData(T *newData) {
        this->data = newData;
    }
    void setLeftChild(Node<T> *newLeftChild) {
        this->leftChild = newLeftChild;
    }
    void setRightChild(Node<T> *newRightChild) {
        this->rightChild = newRightChild;
    }
    void setParent(Node<T> *newParent) {
        this->parent = newParent;
    }

    // Print
    void print() {
        if (data != nullptr) {
            data->print();
        }
    }

    // Compare Data values
    bool compare(const Node<T>* otherNode) const {
        if (this->data == nullptr && otherNode->getData() == nullptr) {
            return 0;  // both are null, equal
        } else if (this->data == nullptr) {
            return -1; // this->data is null, otherNode data is not: (node < otherNode)
        } else if (otherNode->getData() == nullptr) {
            return 1;  // this->data is not null, otherNode data is null: (node > otherNode)
        } else {
            return *this->data < *otherNode->getData() ? -1 : (*otherNode->getData() < *this->data ? 1 : 0);
            // Compare the actual data values using operator <
        }
    }
};


// Data Class: the data that goes inside the node
class Data {
private:
    int sourceVertex;
    int destinationVertex;
    int edgeCost;

public:
    // Constructor
    Data(int source, int destination) {
        this->sourceVertex = source;
        this->destinationVertex = destination;
        edgeCost = 0;
    }

    // Getters
    int getSourceVertex() const {
        return sourceVertex;
    }
    int getDestinationVertex() const {
        return destinationVertex;
    }
    int getEdgeCost() const {
        return edgeCost;
    }

    // Setter
    void setSourceVertex(int newSourceVertex) {
        sourceVertex = newSourceVertex;
    }
    void setDestinationVertex(int newDestinationVertex) {
        destinationVertex = newDestinationVertex;
    }
    void setEdgeCost(int newEdgeCost) {
        edgeCost = newEdgeCost;
    }

    // print the edgeCost
    void print() const {
        cout << sourceVertex << " - " << destinationVertex << " -> " << edgeCost << endl;
    }

    //compare method
};

// Binary Heap Class: Container for Nodes
template<typename T>
class BinaryHeap {
private:
    Node<T> *root;
    int numberOfElements;
    int height;

public:
    // Constructor
    BinaryHeap(T *data) {
        root = new Node<T>(data);
        numberOfElements = 0;
        height = 0;
    }

    // Destructor
    ~BinaryHeap() {
        deleteBH(root);
    }

    void deleteBH(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        // delete left subtree
        deleteBH(node->getLeftChild());
        // delete right subtree
        deleteBH(node->getRightChild());
        // delete the node
        delete node;
    }

    // Getters
    Node<T> *getRoot() const {
        return root;
    }
    int getnumberOfElements() const {
        return numberOfElements;
    }
    int getHeight() const {
        return height;
    }

    // Setters
    void setRoot(Node<T> *newRoot) {
        root = newRoot;
    }
    void setNumberOfElements(int num) {
        numberOfElements = num;
    }
    void setHeight(int newHeight) {
        height = newHeight;
    }

//    // Function to calculate the height of a node
//    int calculateHeight(Node<T> *node) {
//        if (node == nullptr) {
//            return -1; // Height of an empty tree is -1
//        } else {
//            return 1 + max(calculateHeight(node->getLeftChild()), calculateHeight(node->getRightChild()));
//        }
//    }

    Data deleteMin() const {

    }

    // delete element recursively
    Node<T> *deleteElement(T *data) {
        root = deleteNode(root, data);
        if (root != nullptr) {
            numberOfElements--;
        }
        return root; // return updated root node
    }

    void print() {
        if (root != nullptr) {
            root->print();
        }
    }

    void insert(Data data) {

    }

    bool isEmpty() {
        return false;
    }
};

// This method runs the prims algorithm on the graph and prints the output
void runPrims(int G[VERTEXCOUNT][VERTEXCOUNT], BinaryHeap<Data>* binHeap) {
    vector<bool> visited(VERTEXCOUNT, false);
    vector<int> key(VERTEXCOUNT, INT_MAX);
    vector<int> parent(VERTEXCOUNT, -1);
    int start = 0;

    binHeap->insert(Data(start, 0));
    key[start] = 0;

    while (!binHeap->isEmpty()) {
        int u = binHeap->deleteMin().getSourceVertex();

        visited[u] = true;

        for (int v = 0; v < VERTEXCOUNT; v++) {
            if (G[u][v] && !visited[v] && G[u][v] < key[v]) {
                key[v] = G[u][v];
                binHeap->insert(Data(v, key[v]));
                parent[v] = u;
            }
        }
    }

    for (int i = 1; i < VERTEXCOUNT; i++)
        printf("Parent: %d, Vertex: %d, Weight: %d \n", parent[i], i, G[i][parent[i]]);
}

// Main program
int main() {

    cout << "number of vertices in the graph: " << VERTEXCOUNT << endl;

    // initialize graph
    int G[VERTEXCOUNT][VERTEXCOUNT] =
                  {{0, 3, 65, 0, 0},
                   {3, 0, 85, 20, 45},
                   {65, 85, 0, 41, 77},
                   {0, 20, 41, 0, 51},
                   {0, 45, 77, 51, 0}
                  };

    // initialize Binary Heap
    int source = 0; // source vertex
    int destination = 0; // destination vertex
    int cost = G[source][destination]; // cost from adjacency matrix

    Data *newData = new Data(source, destination);

    BinaryHeap<Data> *binHeap = new BinaryHeap<Data>(newData);

    // print statements
    binHeap->print();

    // Print all edge costs
    for(int i = 0; i < VERTEXCOUNT; i++) {
        for(int j = 0; j < VERTEXCOUNT; j++) {
            if(G[i][j] != 0) {
                cout << "Edge cost between " << i << " and " << j << ": " << G[i][j] << endl;
            }
        }
    }

    // call runPrims method
    runPrims(G, binHeap);

    delete binHeap;

    return 0;
}