#pragma once
#include <string>
#include "BST.h"

class FileManager {
public:
    static bool saveBinary(const BST& tree, const std::string& filename);

    static bool loadBinary(BST& tree, const std::string& filename);

    static bool loadTextToBST(BST& tree, const std::string& filename, bool append = false);
};
