#pragma once
#include <string>
#include <functional>
#include "AccountStats.h"

//This class implements an ordered map using an AVL tree
class OrderedMap {
private:

    //this is the node structure for the AVL tree
    struct Node {
        std::string key;
        AccountStats value;
        Node* left;
        Node* right;
        int height;

        //Constructor
        Node(const std::string& k)
            : key(k), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;
    int nodeCount;

    //Returns height of node
    int getHeight(Node* node) const;

    //this is calculating the balance factor
    int getBalance(Node* node) const;

    //AVL rotations
    Node* rotateLeft(Node* x);
    Node* rotateRight(Node* y);

    //this is inserting into the tree
    Node* insert(Node* node, const std::string& key);

    //Find node by key
    Node* findNode(Node* node, const std::string& key) const;

    //this is inorder traversal helper
    void forEachInOrder(Node* node, const std::function<void(const std::string&, const AccountStats&)>& func) const;

    //Deletes entire tree
    void destroy(Node* node);

public:

    //this is constructor/destructor
    OrderedMap();
    ~OrderedMap();

    //Access or insert element
    AccountStats& operator[](const std::string& key);

    //this is find function
    const AccountStats* find(const std::string& key) const;
    AccountStats* find(const std::string& key);

    //Traversal function
    void forEach(const std::function<void(const std::string&, const AccountStats&)>& func) const;

    //this is returning number of elements
    int size() const;
};