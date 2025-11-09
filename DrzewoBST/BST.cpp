#include "BST.h"
#include <fstream>
#include <cstdint>

BST::BST() : root(nullptr) {}
BST::~BST() { clear(); }

void BST::insert(int value) { root = insertRec(root, value); }
BST::Node* BST::insertRec(Node* node, int value) {
    if (!node) return new Node(value);
    if (value < node->value) node->left = insertRec(node->left, value);
    else if (value > node->value) node->right = insertRec(node->right, value);
    return node;
}

bool BST::remove(int value) {
    bool removed = false;
    root = removeRec(root, value, removed);
    return removed;
}

BST::Node* BST::removeRec(Node* node, int value, bool& removed) {
    if (!node) return nullptr;
    if (value < node->value) node->left = removeRec(node->left, value, removed);
    else if (value > node->value) node->right = removeRec(node->right, value, removed);
    else {
        removed = true;
        if (!node->left) { Node* r = node->right; delete node; return r; }
        else if (!node->right) { Node* l = node->left; delete node; return l; }
        else {
            Node* minRight = findMin(node->right);
            node->value = minRight->value;
            node->right = removeRec(node->right, minRight->value, removed);
        }
    }
    return node;
}

BST::Node* BST::findMin(Node* node) const {
    while (node && node->left) node = node->left;
    return node;
}

void BST::clear() { clearRec(root); root = nullptr; }
void BST::clearRec(Node* node) {
    if (!node) return;
    clearRec(node->left);
    clearRec(node->right);
    delete node;
}
