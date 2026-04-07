#include "OrderedMap.h"
#include <algorithm>

//This is the constructor
OrderedMap::OrderedMap() {
    root = nullptr;
    nodeCount = 0;
}

//this is the destructor
OrderedMap::~OrderedMap() {
    destroy(root);
}

//Returns height of node
int OrderedMap::getHeight(Node* node) const {
    if (node == nullptr) return 0;
    return node->height;
}

//this is calculating balance factor
int OrderedMap::getBalance(Node* node) const {
    if (node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

//Right rotation
OrderedMap::Node* OrderedMap::rotateRight(Node* y) {
    Node* x = y->left;
    Node* temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));

    return x;
}

//this is left rotation
OrderedMap::Node* OrderedMap::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));

    return y;
}

//Insert function
OrderedMap::Node* OrderedMap::insert(Node* node, const std::string& key) {

    //this is creating a new node
    if (node == nullptr) {
        nodeCount++;
        return new Node(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    }
    else if (key > node->key) {
        node->right = insert(node->right, key);
    }
    else {
        return node;
    }

    //Update height
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    //this is AVL balancing

    //Left Left
    if (balance > 1 && key < node->left->key) {
        return rotateRight(node);
    }

    //Right Right
    if (balance < -1 && key > node->right->key) {
        return rotateLeft(node);
    }

    //this is Left Right case
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    //Right Left
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

//this is searching for a node
OrderedMap::Node* OrderedMap::findNode(Node* node, const std::string& key) const {
    if (node == nullptr) return nullptr;

    if (key == node->key) return node;

    if (key < node->key) return findNode(node->left, key);

    return findNode(node->right, key);
}

//Operator[] behavior
AccountStats& OrderedMap::operator[](const std::string& key) {
    root = insert(root, key);
    Node* node = findNode(root, key);
    return node->value;
}

//this is const find
const AccountStats* OrderedMap::find(const std::string& key) const {
    Node* node = findNode(root, key);
    if (node == nullptr) return nullptr;
    return &(node->value);
}

//Non-const find
AccountStats* OrderedMap::find(const std::string& key) {
    Node* node = findNode(root, key);
    if (node == nullptr) return nullptr;
    return &(node->value);
}

//this is inorder traversal
void OrderedMap::forEachInOrder(Node* node, const std::function<void(const std::string&, const AccountStats&)>& func) const {
    if (node == nullptr) return;

    forEachInOrder(node->left, func);
    func(node->key, node->value);
    forEachInOrder(node->right, func);
}

//Public traversal
void OrderedMap::forEach(const std::function<void(const std::string&, const AccountStats&)>& func) const {
    forEachInOrder(root, func);
}

//this is returning size
int OrderedMap::size() const {
    return nodeCount;
}

//Destroy tree
void OrderedMap::destroy(Node* node) {
    if (node == nullptr) return;

    destroy(node->left);
    destroy(node->right);
    delete node;
}