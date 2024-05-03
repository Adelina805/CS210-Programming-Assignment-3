#include <iostream>
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
        if (otherNode == nullptr) {
            return false;
        }
        return *(this->data) == *(otherNode->getData());
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

    void heapifyUp(int index) { // heapify
        if (index <= 0) return;
        int parent = (index - 1) / 2;

        if (heap[parent].getEdgeCost() > heap[index].getEdgeCost()) {

            swap(heap[parent], heap[index]);

            heapifyUp(parent);
        }
    }

    void heapifyDown(int index) { // heapify
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < heap.size() && heap[left].getEdgeCost() < heap[smallest].getEdgeCost()) {
            smallest = left;
        }

        if (right < heap.size() && heap[right].getEdgeCost() < heap[smallest].getEdgeCost()) {
            smallest = right;
        }

        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

    void insertElement(T data) {
        heap.push_back(data);
        heapifyUp(heap.size() - 1);
    }

    T deleteMin() {
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

    // initialize visited/unvisited array "0" = false = unvisited and "1" = true = visited
    bool visited[VERTEXCOUNT];
    for (int i = 0; i < VERTEXCOUNT; i++) {
        visited[i] = false; // set all to unvisited
    }

    // add all edges adjacent to the start vertex to the priority queue
    for(int i = 0; i < VERTEXCOUNT; ++i) {
        if(G[0][i] != 0) { // if adjacent insert into the binary heap
            binHeap->insertElement(Data(0, i, G[0][i]));
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
                    binHeap->insertElement(Data(secondVertex, i, G[secondVertex][i]));
                }
            }
        }
    }
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