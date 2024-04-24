#include <iostream>
#include <queue>
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

    // Function to calculate the height of a node
    int calculateHeight(Node<T> *node) {
        if (node == nullptr) {
            return -1; // Height of an empty tree is -1
        } else {
            return 1 + max(calculateHeight(node->getLeftChild()), calculateHeight(node->getRightChild()));
        }
    }

    int findMinKey(int key[], bool mstSet[])
    {
        // Initialize min value
        int min = INT_MAX, min_index;

        for (int v = 0; v < VERTEXCOUNT; v++)
            if (mstSet[v] == false && key[v] < min)
                min = key[v], min_index = v;
        return min_index;
    }

    // delete element recursively
    Node<T> *deleteElement(T *data) {
        root = deleteNode(root, data);
        if (root != nullptr) {
            numberOfElements--;
        }
        return root; // return updated root node
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

    bool operator<(const Data& rhs) const {
        return this->edgeCost > rhs.edgeCost;
    }

    // compare edgeCost
    void compare() const {
        //compare
    }
};

// This method runs the prims algorithm on the graph and prints the output
void runPrims(int G[VERTEXCOUNT][VERTEXCOUNT], BinaryHeap<Data>* binHeap) {
//    int parent[VERTEXCOUNT]; // Array to store constructed MST
//    int key[VERTEXCOUNT];    // Key values used to pick minimum weight edge in cut
//    bool inMST[VERTEXCOUNT];  // To represent set of vertices included in MST
//
//    // Initialize all keys as INFINITE
//    for (int i = 0; i < VERTEXCOUNT; i++) {
//        key[i] = INT_MAX;
//        inMST[i] = false;
//    }
//
//    // Always include first 1st vertex in MST.
//    // Make key 0 so that this vertex is picked as first vertex.
//    key[0] = 0;
//    parent[0] = -1; // First node is always root of MST
//
//    // The MST will have V vertices
//    for (int count = 0; count < VERTEXCOUNT - 1; count++) {
//        // Pick the minimum key vertex from the set of vertices not yet included in MST
//        //int u = binHeap->extractMin();
//
//        // Add the picked vertex to the MST set
//        inMST[u] = true;
//
//        // Update key value and parent index of the adjacent vertices of the picked vertex.
//        // Consider only those vertices which are not yet included in MST
//        for (int v = 0; v < VERTEXCOUNT; v++) {
//            // Update the key only if G[u][v] is smaller than key[v]
//            if (G[u][v] && !inMST[v] && G[u][v] < key[v]) {
//                parent[v] = u;
//                key[v] = G[u][v];
//                binHeap->decreaseKey(v, key[v]);
//            }
//        }
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
    int destination = 1; // destination vertex
    int cost = G[source][destination]; // cost from adjacency matrix

    Data *newData = new Data(source, destination, cost);

    BinaryHeap<Data> *binHeap = new BinaryHeap<Data>(newData);

    // call runPrims method
    runPrims(G, binHeap);

    delete binHeap;

    return 0;
}