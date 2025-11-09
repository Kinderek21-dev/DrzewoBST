#include <iostream>
#include "BST.h"

using namespace std;  

int main() {
    BST tree;
    bool running = true;
    while (running) {
        cout << "1. Dodaj element\n2. Usun element\n3. Wyswietl inorder\n0. Wyjscie\nWybierz: ";
        int opt; cin >> opt;
        if (opt == 1) {
            int v; cin >> v;
            tree.insert(v);
        }
        else if (opt == 2) {
            int v; cin >> v;
            tree.remove(v);
        }
        else if (opt == 3) tree.displayTraversal(BST::INORDER);
        else if (opt == 0) running = false;
    }
    return 0;
}
