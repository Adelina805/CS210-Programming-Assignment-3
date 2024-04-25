#include <iostream>
#include <queue>
#include <vector>
#include <utility>
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

    // compare Data values
    bool compare(const Node<T>* otherNode) const {
        // This class must have a compare method to compare Data values.

    }
};


// Binary Heap Class: Container for Nodes
template<typename T>
class BinaryHeap {
private:
    Node<T> *root;
    int numberOfElements;
    int height;
    vector<T> heap;

    void heapifyUp(int index) {
        if (index <= 0) return;
        int parent = (index - 1) / 2;
        if (heap[parent].weight > heap[index].weight) {
            swap(heap[parent], heap[index]);
            heapifyUp(parent);
        }
    }

    void heapifyDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < heap.size() && heap[left].weight < heap[smallest].weight) {
            smallest = left;
        }

        if (right < heap.size() && heap[right].weight < heap[smallest].weight) {
            smallest = right;
        }

        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

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

    void insert(T data) {
        heap.push_back(data);
        heapifyUp(heap.size() - 1);
    }

    T peek() {
        return heap.front();
    }

    void remove() {
        if (heap.empty()) return;
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    bool isEmpty() {
        return heap.empty();
    }

    void print() {
        for (auto& data : heap) {
            cout << data.getSourceVertex() << " - " << data.getDestinationVertex() << ": " << data.getEdgeCost() << endl;
        }
    }

//    void print() {
//        if (root != nullptr) {
//            root->print();
//        }
//    }

//    // print entire BH recursively
//    void print() const {
//        bool first = true;
//        printBH(root, first);
//        cout << endl;
//    }
//
//    // pre-order print
//    void printBH(Node<T> *node, bool& first) const {
//        if (node == nullptr) {
//            return; // if null node
//        }
//        if (!first) {
//            cout << ", "; // print comma if not the last element
//        }
//        node->getData()->print(); // print node value
//        first = false;
//        printBH(node->getLeftChild(), first); // print left
//        printBH(node->getRightChild(), first); // print right
//    }

    //add an element to the heap
    // this method inserts the data into the heap and heapifies. This method return nothing.
//    Node<T> *insertElementBST(Node<T> *node, T *data) {
//        if (node == nullptr) { // if empty, return node
//            return new Node<T>(data);
//        }
//        if (data->getValue() < node->getData()->getValue()) { // if smaller than parent, left child
//            node->setLeftChild(insertElementBST(node->getLeftChild(), data));
//        }
//        else if (data->getValue() > node->getData()->getValue()) { // if larger than parent, right child
//            node->setRightChild(insertElementBST(node->getRightChild(), data));
//        }
//
//        // After insertion, update the height of the tree
//        height = calculateHeight(root);
//
//        return node;
//    }

//    // Function to calculate the height of a node
//    int calculateHeight(Node<T> *node) {
//        if (node == nullptr) {
//            return -1; // Height of an empty tree is -1
//        } else {
//            return 1 + max(calculateHeight(node->getLeftChild()), calculateHeight(node->getRightChild()));
//        }
//    }

//    int parent(int index) {
//        return (index - 1) / 2;
//    }

    // POP: remove the smallest element from the heap
    // this method finds the smallest element in the tree and returns it to the calling method and heapifies. It returns the data object.
    T deleteMin() { // "POP"
        // Return the smallest element and remove it from the heap
    }

    // find the smallest element in the tree and print it
//    void findSmallest() {
//        Node<T>* smallest = findSmallestHelper(root);
//        if (smallest != nullptr) {
//            smallest->getData()->print();
//            cout << endl;
//        } else {
//            cout << "empty" << endl;
//        }
//    }
//    // recursive function to find the smallest element
//    Node<T>* findSmallestHelper(Node<T>* node) const {
//        if (node == nullptr || node->getLeftChild() == nullptr) {
//            return node;
//        }
//        return findSmallestHelper(node->getLeftChild());
//    }

//    // check if the heap is empty
//    bool empty() {
//        // Return true if the heap is empty, false otherwise
//    }

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

    //compare method to compare values of edgeCost
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

    // Initialize a priority queue to store the edges
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

    // initialize visited/unvisited array "0" = false = unvisited and "1" = true = visited
    bool visited[VERTEXCOUNT];
    for (int i = 0; i < VERTEXCOUNT; i++) {
        visited[i] = false; // set all to unvisited
    }

    // print initial visited/unvisited array
    cout << "visited/unvisited: " << endl;
    for (int i = 0; i < VERTEXCOUNT; i++) {
        cout << visited[i] << " ";
    }
    cout << endl; cout << endl;


    // add all edges from the start vertex to the priority queue
    for(int i = 0; i < VERTEXCOUNT; ++i) {
        if(G[0][i] != 0) {
            pq.push({G[0][i], {0, i}});
        }
    }

    while(!pq.empty()) { // while priority queue is not empty
        auto edge = pq.top(); // get top and store
        pq.pop(); // remove top element

        int weight = edge.first;
        int firstVertex = edge.second.first;
        int secondVertex = edge.second.second;

        // get the edge with the smallest weight
        if (!visited[firstVertex] || !visited[secondVertex]) { // if the edge does not form a cycle

            visited[firstVertex] = visited[secondVertex] = true; // Set the unvisited vertex as visited

            cout << "smallest edge: " << firstVertex << " - " << secondVertex << " -> " << weight << endl;

            // add all edges connected to the new vertex to the priority queue
            for (int i = 0; i < VERTEXCOUNT; ++i) {
                if (G[secondVertex][i] != 0 && !visited[i]) {
                    pq.push({G[secondVertex][i], {secondVertex, i}});
                }
            }
        }
    }
    cout << endl;

    // print updated visited/unvisited array
    cout << "visited/unvisited: " << endl;
    for (int i = 0; i < VERTEXCOUNT; i++) {
        cout << visited[i] << " ";
    }
    cout << endl; cout << endl;

    // print expected output
    cout << "Prim's MST:" << endl;
    binHeap->print();
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
    int j = 2;

    // initialize generic data
    Data *newData = new Data(i, j, G[i][j]);

    // initialize Binary Heap with said data
    BinaryHeap<Data> *binHeap = new BinaryHeap<Data>(newData);

    // call runPrims method
    runPrims(G, binHeap);

    return 0;
}