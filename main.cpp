#include <iostream>
using namespace std;

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

    // insert element recursively
    void insertElement(T *data) {
        root = insertElementBST(root, data);
        numberOfElements++;
    }

    Node<T> *insertElementBST(Node<T> *node, T *data) {
        if (node == nullptr) { // if empty, return node
            return new Node<T>(data);
        }
        if (data->getValue() < node->getData()->getValue()) { // if smaller than parent, left child
            node->setLeftChild(insertElementBST(node->getLeftChild(), data));
        }
        else if (data->getValue() > node->getData()->getValue()) { // if larger than parent, right child
            node->setRightChild(insertElementBST(node->getRightChild(), data));
        }

        // After insertion, update the height of the tree
        height = calculateHeight(root);

        return node;
    }

    // find the smallest element in the tree and print it
    void findSmallest() {
        Node<T>* smallest = findSmallestHelper(root);
        if (smallest != nullptr) {
            smallest->getData()->print();
            cout << endl;
        } else {
            cout << "empty" << endl;
        }
    }

    // recursive function to find the smallest element
    Node<T>* findSmallestHelper(Node<T>* node) const {
        if (node == nullptr || node->getLeftChild() == nullptr) {
            return node;
        }
        return findSmallestHelper(node->getLeftChild());
    }

    // delete element recursively
    Node<T> *deleteElement(T *data) {
        root = deleteNode(root, data);
        if (root != nullptr) {
            numberOfElements--;
        }
        return root; // return updated root node
    }

    // Recursive function to delete the entire Binary Heap
    void deleteMin(Node<T>* node) {
        if (node == nullptr)
            return;

        // Recursively delete left and right subtrees
        deleteBH(node->getLeftChild());
        deleteBH(node->getRightChild());

        // Delete the current node
        delete node;
    }
};


// Data Class: the data that goes inside the node
class Data {
private:
    int value;

public:
    // Constructor
    Data(int value) {
        this->value = value;
    }

    // Getter
    int getValue() const {
        return value;
    }

    // Setter
    void setValue(int newValue) {
        value = newValue;
    }

    // print the value
    void print() const {
        cout << value;
    }
};

// Main program
int main() {
//    int i;
//    int j;

    int G[i][j] =  {{0, 3, 65, 0, 0},
                   {3, 0, 85, 20, 45},
                   {65, 85, 0, 41, 77},
                   {0, 20, 41, 0, 51},
                   {0, 45, 77, 51, 0}};

//    int a[] = {10, 45, 23, 67, 89, 34, 12, 99};
//    Data *newData = new Data(a[0]);
//    BinarySearchTree<Data> *newBST = new BinarySearchTree<Data>(newData);
//    for (int i = 1; i < (sizeof(a) / sizeof(int)); i++) {
//        newData = new Data(a[i]);
//        newBST->insertElement(newData);
//    }
//    newBST->print();

    return 0;
}