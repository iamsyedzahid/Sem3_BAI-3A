#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

int height(Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int getBalance(Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

Node* insert(Node* node, int key) {
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));
    
    return node;
}

void inOrder(Node *root) {
    if(root != NULL) {
        inOrder(root->left);
        cout << root->key << " (BF: " << getBalance(root) << ", H: " << root->height << ") | ";
        inOrder(root->right);
    }
}

int main() {
    Node *root = NULL;
    int keys[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        root = insert(root, keys[i]);
    }
    
    cout << "Initial Balanced Tree (Inorder): ";
    inOrder(root);
    cout << "\nRoot: " << root->key << endl;
    
    root = insert(root, 55);
    
    cout << "\nTree after inserting 55 (Inorder): ";
    inOrder(root);
    cout << "\nRoot: " << root->key << endl; 

    root = leftRotate(root);

    cout << "\nResulting Tree after Left Rotation on the root (Inorder): ";
    inOrder(root);
    cout << "\nNew Root: " << root->key << endl; 
    
    return 0;
}
