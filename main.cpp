#include <iostream>
#include <utility>
using namespace std;

// save

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

    // compare Data values
    bool compare(const Node<T>* otherNode) const {
        if (otherNode == nullptr) {
            return false;
        }
        return *(this->data) == *(otherNode->getData());
    }

    bool getEdgeCost() {
        return false;
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
        Node<T> *newNode = new Node<T>(data);
        root = newNode;
        numberOfElements = 2;
        height = 0;
    }

    // Destructor
    ~BinaryHeap() {
        deleteBH(root);
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

    void deleteBH(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        // recursively delete left and right subtrees
        deleteBH(node->getLeftChild());
        deleteBH(node->getRightChild());

        // delete the current node
        delete node;
    }

    void heapifyUp(Node<T>* node) { // heapify
        if (node == root) return;
        Node<T>* parent = node->getParent();

        if (parent->getEdgeCost() > node->getEdgeCost()) {
            swap(parent, node);
            heapifyUp(parent);
        }
    }

    void heapifyDown(Node<T>* node) { // heapify
        Node<T>* left = node->getLeftChild();
        Node<T>* right = node->getRightChild();
        Node<T>* smallest = node;

        if (left != nullptr && left->getEdgeCost() < smallest->getEdgeCost()) {
            smallest = left;
        }

        if (right != nullptr && right->getEdgeCost() < smallest->getEdgeCost()) {
            smallest = right;
        }

        if (smallest != node) {
            swap(node, smallest);
            heapifyDown(smallest);
        }
    }

    // insert element recursively
    void insertElement(T *data) {
        root = insertElementBH(root, data);
        numberOfElements++;
    }

    Node<T> *insertElementBH(Node<T> *node, T *data) {
        if (node == nullptr) { // if empty, return node
            return new Node<T>(data);
        }
        if (data->getEdgeCost() < node->getData()->getEdgeCost()) { // if smaller than parent, left child
            node->setLeftChild(insertElementBH(node->getLeftChild(), data));
        }
        else if (data->getEdgeCost() > node->getData()->getEdgeCost()) { // if larger than parent, right child
            node->setRightChild(insertElementBH(node->getRightChild(), data));
        }

        // After insertion, update the height of the tree
        height = calculateHeight(root);

        return node;
    }

    // Function to calculate the height of a node
    int calculateHeight(Node<T> *node) {
        if (node == nullptr) {
            return -1; // Height of an empty tree is -1
        } else {
            return 1 + max(calculateHeight(node->getLeftChild()), calculateHeight(node->getRightChild()));
        }
    }

    T deleteMin() {
        return *root->getData();
    }

    Node<T> *findLastNode(Node<T> *pNode) {
        return nullptr;
    }

    void remove() {
        if (root == nullptr) return;
        // You need to implement a method to find the last node in the heap
        Node<T>* lastNode = findLastNode(root);
        root->setData(lastNode->getData());
        delete lastNode;
        heapifyDown(root);
    }

    bool isEmpty() {
        return root == nullptr;
    }

    void print() {
        if (root != nullptr) {
            T data = *root->getData();
            cout << data.getSourceVertex() << " - " << data.getDestinationVertex() << ": " << data.getEdgeCost() << endl;
        } else {
            cout << "Heap is empty." << endl;
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
        sourceVertex = source;
        destinationVertex = destination;
        edgeCost = cost;
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

    // print the vertex info
    void print() const {
        cout << sourceVertex << " - " << destinationVertex << " -> " << edgeCost << endl;
    }

    // compare edgeCost values
    bool compare(const Data& otherData) const {
        return this->edgeCost == otherData.getEdgeCost();
    }
};


// This method runs the prims algorithm on the graph and prints the output
void runPrims(int G[VERTEXCOUNT][VERTEXCOUNT], BinaryHeap<Data>* binHeap) {

    // DELETE LATER
    // Print initial graph and all edge costs
    cout << "Initial Graph:" << endl;
    for(int i = 0; i < VERTEXCOUNT; i++) {
        for(int j = 0; j < VERTEXCOUNT; j++) {
            cout << "   " << i << " - " << j << ": " << G[i][j] << endl;
        }
    }
    cout << endl;

    // initialize visited/unvisited array "0" = false = unvisited and "1" = true = visited
    bool visited[VERTEXCOUNT];
    for (int i = 0; i < VERTEXCOUNT; i++) {
        visited[i] = false; // set all to unvisited
    }

    // DELETE LATER
    // print visited/unvisited array
    cout << "updated visited/unvisited: " << endl;
    for (int i = 0; i < VERTEXCOUNT; i++) {
        cout << visited[i] << " ";
    }
    cout << endl;
    cout << endl;
    cout << "Prim's MST:" << endl;
    binHeap->print();
    cout << endl; // if ALL vertices are visited and "true" the program ends


    // add all edges adjacent to the start vertex to the priority queue
    for(int i = 0; i < VERTEXCOUNT; ++i) {
        if(G[0][i] != 0) { // if adjacent insert into the binary heap
            binHeap->insertElement(new Data(0, i, G[0][i]));
        }
    }

    // print expected output
    cout << "Prim's MST is Edge -> Cost" << endl;

    while(!binHeap->isEmpty()) { // while priority queue is not empty
        Data edge = binHeap->deleteMin(); // get smallest and delete
        binHeap->remove(); // remove it from priority queue

        int firstVertex = edge.getSourceVertex();
        int secondVertex = edge.getDestinationVertex();

        // if the edge does not form a cycle (if at least one has not been visited)
        if (!visited[firstVertex] || !visited[secondVertex]) {

            visited[firstVertex] = visited[secondVertex] = true; // set both the vertices as visited

            cout << firstVertex << " - " << secondVertex << " -> " << edge.getEdgeCost() << endl; // print the vertex and it's the min edge cost

            // add all edges adjacent to the new vertex to the priority queue
            for (int i = 0; i < VERTEXCOUNT; ++i) {
                if (G[secondVertex][i] != 0 && !visited[i]) { // if adjacent and unvisited, add to pq and insert into the binary heap
                    binHeap->insertElement(new Data(secondVertex, i, G[secondVertex][i]));
                }
            }
        }
        binHeap->print();
        cout << "print 1" << endl;
    }
    binHeap->print();
    cout << "print 2 " << endl;
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

    int i = 0; // source vertex
    int j = 0; // destination vertex

    // initialize data
    Data *newData = new Data(i, j, G[i][j]);

    // initialize Binary Heap
    BinaryHeap<Data> *binHeap = new BinaryHeap<Data>(newData);

    // call runPrims method
    runPrims(G, binHeap);

    // clear memory
    delete binHeap;

    return 0;
}