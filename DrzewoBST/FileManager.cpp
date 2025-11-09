#include "FileManager.h"
#include <fstream>
#include <iostream>

bool FileManager::saveBinary(const BST& tree, const std::string& filename) {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) return false;
    tree.serializeBinary(ofs);
    return true;
}

bool FileManager::loadBinary(BST& tree, const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs) return false;
    tree.deserializeBinary(ifs);
    return true;
}

bool FileManager::loadTextToBST(BST& tree, const std::string& filename, bool append) {
    std::ifstream ifs(filename);
    if (!ifs) return false;
    if (!append) tree.clear();
    int v;
    while (ifs >> v) {
        tree.insert(v);
    }
    return true;
}