#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream>

const int SIZE_KEY = 256;
using TKey = char;
using TValue = unsigned long long;

class TAVL {
public:
    struct TNode { // структура для представления узлов дерева 
        TNode() {
            Left = Right = nullptr;
            Height = 1;
        }
        TNode(TKey* key, TValue value) {
            Key = Substitution(key);
            Value = value;
            Left = Right = nullptr;
            Height = 1;
        }
        ~TNode() {
            delete[] Key;
        }
        TKey* Substitution(TKey* key) {
            if (key == nullptr) {
                return nullptr;
            }
            char* sub = new TKey[SIZE_KEY + 1];
            memcpy(sub, key, strlen(key));
            memset(sub + strlen(key), '\0', SIZE_KEY + 1 - strlen(key));
            return sub;
        }
        TKey* Key = nullptr;
        TValue Value = 0;
        unsigned char Height;
        TNode* Left = nullptr;
        TNode* Right = nullptr;
    };

    TNode* Root; // корень дерева

    TAVL() {
        Root = nullptr;
    }

    ~TAVL() {
        DeleteTree(Root);
    }

    void DeleteTree(TNode* root) { // Удаление дерева
        if (root != nullptr) {
            DeleteTree(root->Left);
            DeleteTree(root->Right);
            delete root;
        }
    }

    int CompareKeys(TKey* lhs, TKey* rhs) { // Сравнение ключей
        return strcmp(lhs, rhs);
    }

    unsigned char GetHeight(TNode* p) {
        return p ? p->Height : 0;
    }

    int BFactor(TNode* p) {
        return GetHeight(p->Right) - GetHeight(p->Left);
    }

    void FixHeight(TNode* p) {
        unsigned char hl = GetHeight(p->Left);
        unsigned char hr = GetHeight(p->Right);
        p->Height = (hl > hr ? hl : hr) + 1;
    }

    TNode* RotateRight(TNode* p) { // Правый поворот вокруг p
        TNode* q = p->Left;
        p->Left = q->Right;
        q->Right = p;
        FixHeight(p);
        FixHeight(q);
        return q;
    }

    TNode* RotateLeft(TNode* q) { // Левый поворот вокруг q
        TNode* p = q->Right;
        q->Right = p->Left;
        p->Left = q;
        FixHeight(q);
        FixHeight(p);
        return p;
    }

    TNode* Balance(TNode* p) { // Балансировка узла p
        FixHeight(p);
        if (BFactor(p) == 2)
        {
            if (BFactor(p->Right) < 0)
                p->Right = RotateRight(p->Right);
            return RotateLeft(p);
        }
        if (BFactor(p) == -2)
        {
            if (BFactor(p->Left) > 0)
                p->Left = RotateLeft(p->Left);
            return RotateRight(p);
        }
        return p; // балансировка не нужна
    }

    TNode* Insert(TNode* p, TKey* key, TValue value) { // Вставка ключа k в дерево с корнем p
        if (p == nullptr) {
            p = new TNode(key, value);
            std::cout << "OK\n";
            return p;
        }
        if (CompareKeys(key, p->Key) < 0) {
            p->Left = Insert(p->Left, key, value);
        }
        else if (CompareKeys(key, p->Key) > 0) {
            p->Right = Insert(p->Right, key, value);
        }
        else {
            std::cout << "Exist\n";
        }
        return Balance(p);
    }

    TNode* FindMin(TNode* p) { // Поиск узла с минимальным ключом в дереве p 
        return p->Left ? FindMin(p->Left) : p;
    }

    TNode* RemoveMin(TNode* p) { // Удаление узла с минимальным ключом из дерева p
        if (p->Left == 0)
            return p->Right;
        p->Left = RemoveMin(p->Left);
        return Balance(p);
    }

    TNode* Remove(TNode* p, TKey* key) { // Удаление ключа k из дерева p
        if (p == nullptr) {
            std::cout << "NoSuchWord\n";
            return nullptr;
        }
        if (CompareKeys(key, p->Key) < 0)
            p->Left = Remove(p->Left, key);
        else if (CompareKeys(key, p->Key) > 0)
            p->Right = Remove(p->Right, key);
        else //  k == p->Key 
        {
            TNode* q = p->Left;
            TNode* r = p->Right;
            delete p;
            std::cout << "OK\n";
            if (r == nullptr) return q;
            TNode* min = FindMin(r);
            min->Right = RemoveMin(r);
            min->Left = q;
            return Balance(min);
        }
        return Balance(p);
    }

    TNode* Find(TNode* node, TKey* key) { // Поиск элемента
        if (node == nullptr) {
            return nullptr;
        }
        if (CompareKeys(node->Key, key) > 0) {
            return Find(node->Left,key);
        }
        else if (CompareKeys(node->Key, key) < 0) {
            return Find(node->Right,key);
        }
        else {
            return node;
        }
        return nullptr;
    }

    void PrintFind(TKey* key) { // Печать результатов поиска
        TNode* res = Find(Root, key);
        if (res != nullptr) {
            std::cout << "OK: " << res->Value << std::endl;
        }
        else {
            std::cout << "NoSuchWord\n";
        }
    }

    void Save(std::ostream& file, TNode* node) { // Сохранение в файл
        if (node == nullptr) {
            return;
        }
        int keySize = strlen(node->Key);
        file.write((char*)&keySize, sizeof(int));
        file.write(node->Key, keySize);
        file.write((char*)&(node->Value), sizeof(TValue));

        bool hasLeft = (node->Left != nullptr);
        bool hasRight = (node->Right != nullptr);

        file.write((char*)&hasLeft, sizeof(bool));
        file.write((char*)&hasRight, sizeof(bool));

        if (hasLeft) {
            Save(file, node->Left);
        }
        if (hasRight) {
            Save(file, node->Right);
        }
    }

    TNode* Load(std::istream& file, TNode* node) { // Загрузка из файла
        TNode* root = nullptr;

        int keysize;
        file.read((char*)&keysize, sizeof(int));

        if (file.gcount() == 0) {
            return root;
        }

        TKey* key = new char[keysize + 1];
        key[keysize] = '\0';
        file.read(key, keysize);

        TValue value;
        file.read((char*)&value, sizeof(TValue));

        bool hasLeft = false;
        bool hasRight = false;
        file.read((char*)&hasLeft, sizeof(bool));
        file.read((char*)&hasRight, sizeof(bool));

        root = new TNode(key,value);
        if (hasLeft) {
            root->Left = Load(file, root);
        }
        else {
            root->Left = nullptr;
        }

        if (hasRight) {
            root->Right = Load(file, root);
        }
        else {
            root->Right = nullptr;
        }
        delete[] key;
        return root;
    }
};



void DoLower(TKey* key) {
    int lengh = strlen(key);
    for (int i = 0; i < lengh; i++) {
        key[i] = tolower(key[i]);
    }
}

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    TAVL tree;
    TKey key[SIZE_KEY + 1];
    TValue value;

    std::ofstream ofstr;
    std::ifstream ifstr;

    while (std::cin >> key) {
        if (key[0] == '+') {
            std::cin >> key >> value;
            DoLower(key);
            tree.Root = tree.Insert(tree.Root, key, value);
        }
        else if (key[0] == '-') {
            std::cin >> key;
            DoLower(key);
            tree.Root = tree.Remove(tree.Root, key);
        }
        else if (key[0] == '!' && strlen(key) == 1) {
            std::cin >> key;
            if (key[0] == 'S') {
                std::cin >> key;
                ofstr.open(key, std::ios::out | std::ios::binary);
                if (ofstr) {
                    tree.Save(ofstr, tree.Root);
                    std::cout << "OK\n";
                }
                else {
                    std::cout << "ERROR: can't open file\n";
                }
                ofstr.close();
            }
            else if (key[0] == 'L') {
                std::cin >> key;
                ifstr.open(key, std::ios::in | std::ios::binary);
                if (ifstr) {
                    tree.DeleteTree(tree.Root);
                    tree.Root = tree.Load(ifstr, nullptr);
                    std::cout << "OK\n";
                    ifstr.close();
                }
                else {
                    std::cout << "ERROR: can't open file\n";
                }
            }
        }
        else {
            DoLower(key);
            tree.PrintFind(key);
        }
    }
    return 0;
}
