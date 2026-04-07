#pragma once
#include <string>
#include <functional>
#include "AccountStats.h"

//This class implements a custom hash map using chaining
class HashMap {
private:

    //this is the node used for each linked list in the buckets
    struct Node {
        std::string key;
        AccountStats value;
        Node* next;

        //Constructor
        Node(const std::string& k)
            : key(k), next(nullptr) {}
    };

    Node** buckets;
    int bucketCount;
    int elementCount;

    //Returns hash value for a key
    unsigned long hash(const std::string& key) const;

    //this is finding a node by key
    Node* findNode(const std::string& key) const;

    //Deletes all nodes in the table
    void destroy();

public:

    //this is constructor/destructor
    HashMap(int initialBuckets = 100003);
    ~HashMap();

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