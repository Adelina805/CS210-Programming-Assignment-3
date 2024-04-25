#include <iostream>
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
    Data(int source, int destination, int cost) {
        this->sourceVertex = source;
        this->destinationVertex = destination;
        this->edgeCost = cost;
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

    //compare method to compare value of edgeCost.
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
    int getNumberOfElements() const {
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

    T* deleteMin() const {
        if (root == nullptr) {
            return nullptr; // Heap is empty
        }


        return nullptr;
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

    void decreaseKey(int i, int i1) {

    }

    Data extractMin() {
        return Data(0, 0, 0);
    }

    int getKey(int i) {
        return 0;
    }
};


// This method runs the prims algorithm on the graph and prints the output
void runPrims(int G[VERTEXCOUNT][VERTEXCOUNT], BinaryHeap<Data>* binHeap) {

    // Print initial graph and all edge costs
    cout << "Initial Graph:" << endl;
    for(int i = 0; i < VERTEXCOUNT; i++) {
        for(int j = 0; j < VERTEXCOUNT; j++) {
            cout << "   " << i << " - " << j << ": " << G[i][j] << endl;
        }
    }
    cout << endl;

    // initialize visited/unvisited array
    // "0" = false = unvisited
    // "1" = true = visited
    bool visited[VERTEXCOUNT];
    for (int i = 0; i < VERTEXCOUNT; i++) {
        visited[i] = false;
    }

    // print visited/unvisited array
    cout << "initial visited/unvisited: " << endl;
    for (int i = 0; i < VERTEXCOUNT; i++) {
        cout << visited[i] << " ";
    }
    cout << endl;
    cout << endl;

    // pick arbitrary start vertex 0
    visited[0] = true; // set to visited

    for(int j = 0; j < VERTEXCOUNT; ++j) {
        // check all the edges connected to the vertex
        int smallest = 1000;
        int vertex;
        for (int i = 0; i < VERTEXCOUNT; ++i) {
            if (G[j][i] < smallest && G[j][i] != 0) {
                if (!visited[i] || !visited[j]) {
                    smallest = G[j][i]; // Pick the lowest cost edge
                    vertex = i;
                }
            }
        }
        if(smallest != 1000) { // if an edge was found
            cout << "found smallest edge: " << smallest << " at vertices: " << j << " - " << vertex << endl;
            // set chosen vertex to visited
            visited[vertex] = true;
        }
    }
    cout << endl;

    // print visited/unvisited array
    cout << "updated visited/unvisited: " << endl;
    for (int i = 0; i < VERTEXCOUNT; i++) {
        cout << visited[i] << " ";
    }
    cout << endl;
    cout << endl;

    cout << "Prim's MST:" << endl;
    binHeap->print();
    // if ALL vertices are visited and "true" the program ends
}


// Main program
int main() {

    // initialize graph
    int G[VERTEXCOUNT][VERTEXCOUNT] =
                  {{0, 3, 65, 0, 0},
                   {3, 0, 85, 20, 45},
                   {65, 85, 0, 41, 77},
                   {0, 20, 41, 0, 51},
                   {0, 45, 77, 51, 0}
                  };

    int i = 0;
    int j = 0;

    // initialize generic data
    Data *newData = new Data(i, j, G[i][j]);

    // initialize Binary Heap with said data
    BinaryHeap<Data> *binHeap = new BinaryHeap<Data>(newData);

    // call runPrims method
    runPrims(G, binHeap);

    return 0;
}