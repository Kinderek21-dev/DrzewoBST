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
void BST::traverse(Node* node, Traversal t, std::vector<int>& out) const {
    if (!node) return;
    if (t == PREORDER) {
        out.push_back(node->value);
        traverse(node->left, t, out);
        traverse(node->right, t, out);
    }
    else if (t == INORDER) {
        traverse(node->left, t, out);
        out.push_back(node->value);
        traverse(node->right, t, out);
    }
    else {
        traverse(node->left, t, out);
        traverse(node->right, t, out);
        out.push_back(node->value);
    }
}

void BST::displayTraversal(Traversal t) const {
    std::vector<int> out;
    traverse(root, t, out);
    for (int v : out) std::cout << v << " ";
    std::cout << std::endl;
}

bool BST::saveToText(const std::string& filename, Traversal t) const {
    std::ofstream ofs(filename);
    if (!ofs) return false;
    std::vector<int> out;
    traverse(root, t, out);
    for (int v : out) ofs << v << "\n";
    return true;
}

std::vector<int> BST::findPath(int value) const {
    std::vector<int> path;
    if (findPathRec(root, value, path)) return path;
    return std::vector<int>();
}

bool BST::findPathRec(Node* node, int value, std::vector<int>& path) const {
    if (!node) return false;
    path.push_back(node->value);
    if (node->value == value) return true;
    if ((value < node->value && findPathRec(node->left, value, path)) ||
        (value > node->value && findPathRec(node->right, value, path)))
        return true;
    path.pop_back();
    return false;
}

void BST::displayGraphical() const {
    printSideways(root, 0);
}

void BST::printSideways(Node* node, int indent) const {
    if (!node) return;
    printSideways(node->right, indent + 4);
    for (int i = 0; i < indent; ++i) std::cout << ' ';
    std::cout << node->value << std::endl;
    printSideways(node->left, indent + 4);
}

void BST::serializeBinary(std::ostream& os) const {
    serializeBinaryRec(root, os);
}

void BST::serializeBinaryRec(Node* node, std::ostream& os) const {
    if (!node) {
        char marker = 0;
        os.write(&marker, 1);
        return;
    }
    char marker = 1;
    os.write(&marker, 1);
    int32_t v = static_cast<int32_t>(node->value);
    os.write(reinterpret_cast<const char*>(&v), sizeof(v));
    serializeBinaryRec(node->left, os);
    serializeBinaryRec(node->right, os);
}

BST::Node* BST::deserializeBinaryRec(std::istream& is) {
    char marker;
    if (!is.read(&marker, 1)) return nullptr;
    if (marker == 0) return nullptr;
    int32_t v;
    is.read(reinterpret_cast<char*>(&v), sizeof(v));
    Node* node = new Node(static_cast<int>(v));
    node->left = deserializeBinaryRec(is);
    node->right = deserializeBinaryRec(is);
    return node;
}

void BST::deserializeBinary(std::istream& is) {
    clear();
    root = deserializeBinaryRec(is);
}