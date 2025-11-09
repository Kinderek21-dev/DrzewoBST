#include <iostream>
#include <string>
#include "BST.h"
#include "FileManager.h"

using namespace std;

BST::Traversal chooseTraversal() {
    int t;
    cout << "Wybierz typ przegladania: 1=preorder, 2=inorder, 3=postorder: ";
    cin >> t;
    if (t == 1) return BST::PREORDER;
    if (t == 2) return BST::INORDER;
    return BST::POSTORDER;
}

void printMenu() {
    cout << "-------- MENU Drzewo BST --------\n";
    cout << "1. Dodaj element\n";
    cout << "2. Usun element\n";
    cout << "3. Usun cale drzewo\n";
    cout << "4. Szukaj drogi do elementu\n";
    cout << "5. Wyswietl drzewo graficznie\n";
    cout << "6. Wyswietl drzewo (pre/in/post)\n";
    cout << "7. Zapis do pliku tekstowego\n";
    cout << "8. Zapis binarny drzewa\n";
    cout << "9. Wczytaj drzewo z pliku binarnego\n";
    cout << "10. Wczytaj plik tekstowy z liczbami\n";
    cout << "0. Wyjscie\n";
    cout << "Wybierz opcje: ";
}

int main() {
    BST tree;
    bool running = true;

    while (running) {
        printMenu();
        int opt;
        if (!(cin >> opt)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Nieprawidlowe wejscie. Sprobuj ponownie.\n";
            continue;
        }

        switch (opt) {
        case 1: {
            int v; cout << "Podaj wartosc: "; cin >> v; tree.insert(v); break;
        }
        case 2: {
            int v; cout << "Podaj wartosc do usuniecia: "; cin >> v;
            if (tree.remove(v)) cout << "Usunieto.\n"; else cout << "Brak elementu.\n";
            break;
        }
        case 3: {
            tree.clear();
            cout << "Drzewo wyczyszczone\n"; break;
        }
        case 4: {
            int v; cout << "Podaj wartosc do wyszukania: "; cin >> v;
            auto path = tree.findPath(v);
            if (path.empty()) cout << "Element nie znaleziony.\n";
            else {
                cout << "Sciezka: ";
                for (int x : path) cout << x << " ";
                cout << "\n";
            }
            break;
        }
        case 5: {
            tree.displayGraphical(); break;
        }
        case 6: {
            auto t = chooseTraversal();
            tree.displayTraversal(t);
            break;
        }
        case 7: {
            string filename; cout << "Plik tekstowy (nazwa): "; cin >> filename;
            auto t = chooseTraversal();
            if (tree.saveToText(filename, t)) cout << "Zapisano.\n";
            else cout << "Blad zapisu.\n";
            break;
        }
        case 8: {
            string filename; cout << "Plik binarny (nazwa): "; cin >> filename;
            if (FileManager::saveBinary(tree, filename)) cout << "Zapis binarny zakonczony.\n";
            else cout << "Blad zapisu.\n";
            break;
        }
        case 9: {
            string filename; cout << "Plik binarny do wczytania: "; cin >> filename;
            if (FileManager::loadBinary(tree, filename)) cout << "Wczytano drzewo z pliku.\n";
            else cout << "Blad odczytu.\n";
            break;
        }
        case 10: {
            string filename; cout << "Plik tekstowy z liczbami: "; cin >> filename;
            cout << "Dodaj do istniejacego drzewa? (1=tak, 0=nie): "; int a; cin >> a;
            if (FileManager::loadTextToBST(tree, filename, a == 1)) cout << "Wczytano plik tekstowy.\n";
            else cout << "Blad wczytywania.\n";
            break;
        }
        case 0: running = false; break;
        default: cout << "Nieznana opcja.\n";
        }
    }

    cout << "Koniec programu.\n";
    return 0;
}