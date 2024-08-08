#include <iostream>
using namespace std;

struct Node {
    int key;
    int level;
    Node* left;
    Node* right;
    
    Node(int k, int l) : key(k), level(l), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    Node* root;

    Node* insert(Node* node, int key, int level) {
        if (node == nullptr) {
            return new Node(key, level);
        }
        if (key < node->key) {
            node->left = insert(node->left, key, level + 1);
        } else {
            node->right = insert(node->right, key, level + 1);
        }
        return node;
    }

    Node* findMin(Node* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* remove(Node* node, int key) {
        if (node == nullptr) {
            cout << "ERRO" << endl;
            return node;
        }
        if (key < node->key) {
            node->left = remove(node->left, key);
        } else if (key > node->key) {
            node->right = remove(node->right, key);
        } else {
            if (node->left && node->right) {
                Node* temp = findMin(node->right);
                node->key = temp->key;
                node->right = remove(node->right, temp->key);
            } else {
                Node* temp = node;
                node = (node->left) ? node->left : node->right;
                delete temp;
            }
        }
        updateLevels(node, node ? node->level : 0);
        return node;
    }

    void updateLevels(Node* node, int level) {
        if (node == nullptr) return;
        node->level = level;
        updateLevels(node->left, level + 1);
        updateLevels(node->right, level + 1);
    }

    void inorder(Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->key << "/" << node->level << " ";
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (node == nullptr) return;
        cout << node->key << "/" << node->level << " ";
        preorder(node->left);
        preorder(node->right);
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key, 0);
    }

    void remove(int key) {
        root = remove(root, key);
    }

    void printInOrder() {
        inorder(root);
        cout << endl;
    }

    void printPreOrder() {
        preorder(root);
        cout << endl;
    }
};

int main() {
    BinarySearchTree bst;
    char command;
    int key;

    while (cin >> command) {
        if (command == 'f') {
            break;
        }
        switch (command) {
            case 'i':
                cin >> key;
                bst.insert(key);
                break;
            case 'r':
                cin >> key;
                bst.remove(key);
                break;
            case 'o':
                bst.printInOrder();
                break;
            case 'p':
                bst.printPreOrder();
                break;
        }
    }

    return 0;
}