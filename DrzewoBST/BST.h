#pragma once
#include <vector>
#include <string>
#include <iostream>

class BST {
public:
    struct Node {
        int value;
        Node* left;
        Node* right;
        Node(int v) : value(v), left(nullptr), right(nullptr) {}
    };

    enum Traversal { PREORDER = 1, INORDER = 2, POSTORDER = 3 };

    BST();
    ~BST();

    void insert(int value);
    bool remove(int value);
    void clear();
    std::vector<int> findPath(int value) const;
    void displayGraphical() const;
    void displayTraversal(Traversal t) const;
    bool saveToText(const std::string& filename, Traversal t) const;
    void serializeBinary(std::ostream& os) const;
    void deserializeBinary(std::istream& is);

private:
    Node* root;
    Node* insertRec(Node* node, int value);
    Node* removeRec(Node* node, int value, bool& removed);
    Node* findMin(Node* node) const;
    void clearRec(Node* node);
    bool findPathRec(Node* node, int value, std::vector<int>& path) const;
    void printSideways(Node* node, int indent) const;
    void traverse(Node* node, Traversal t, std::vector<int>& out) const;
    void serializeBinaryRec(Node* node, std::ostream& os) const;
    Node* deserializeBinaryRec(std::istream& is);
};
