#include "HashMap.h"

//This is the constructor
HashMap::HashMap(int initialBuckets) {
    bucketCount = initialBuckets;
    elementCount = 0;

    buckets = new Node*[bucketCount];
    for (int i = 0; i < bucketCount; i++) {
        buckets[i] = nullptr;
    }
}

//this is the destructor
HashMap::~HashMap() {
    destroy();
}

//Returns hash value for a string key
unsigned long HashMap::hash(const std::string& key) const {
    unsigned long hashValue = 5381;

    for (char c : key) {
        hashValue = ((hashValue << 5) + hashValue) + static_cast<unsigned long>(c);
    }

    return hashValue % bucketCount;
}

//this is finding a node in the hash table
HashMap::Node* HashMap::findNode(const std::string& key) const {
    unsigned long index = hash(key);
    Node* current = buckets[index];

    while (current != nullptr) {
        if (current->key == key) {
            return current;
        }
        current = current->next;
    }

    return nullptr;
}

//Operator[] behavior
AccountStats& HashMap::operator[](const std::string& key) {
    Node* found = findNode(key);

    //this is returning the value if key already exists
    if (found != nullptr) {
        return found->value;
    }

    unsigned long index = hash(key);
    Node* newNode = new Node(key);

    //Insert new node at front of list
    newNode->next = buckets[index];
    buckets[index] = newNode;
    elementCount++;

    return newNode->value;
}

//this is const find
const AccountStats* HashMap::find(const std::string& key) const {
    Node* node = findNode(key);
    if (node == nullptr) return nullptr;
    return &(node->value);
}

//Non-const find
AccountStats* HashMap::find(const std::string& key) {
    Node* node = findNode(key);
    if (node == nullptr) return nullptr;
    return &(node->value);
}

//this is traversing every bucket and node
void HashMap::forEach(const std::function<void(const std::string&, const AccountStats&)>& func) const {
    for (int i = 0; i < bucketCount; i++) {
        Node* current = buckets[i];

        while (current != nullptr) {
            func(current->key, current->value);
            current = current->next;
        }
    }
}

//Returns size of map
int HashMap::size() const {
    return elementCount;
}

//this is deleting all nodes in the table
void HashMap::destroy() {
    for (int i = 0; i < bucketCount; i++) {
        Node* current = buckets[i];

        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }

        buckets[i] = nullptr;
    }

    delete[] buckets;
    buckets = nullptr;
}