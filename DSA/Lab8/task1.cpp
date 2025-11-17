#include <iostream>
using namespace std;

struct node {
    int data;
    node* left;
    node* right;
};

class bst {
    node* root;

    node* insertnode(node* root, int value) {
        if (root == NULL) {
            node* newnode = new node;
            newnode->data = value;
            newnode->left = newnode->right = NULL;
            return newnode;
        }
        if (value < root->data)
            root->left = insertnode(root->left, value);
        else if (value > root->data)
            root->right = insertnode(root->right, value);
        return root;
    }

    node* findmin(node* root) {
        while (root && root->left != NULL)
            root = root->left;
        return root;
    }

    node* deletenode(node* root, int value) {
        if (root == NULL) return root;

        if (value < root->data)
            root->left = deletenode(root->left, value);
        else if (value > root->data)
            root->right = deletenode(root->right, value);
        else {
            if (root->left == NULL) {
                node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == NULL) {
                node* temp = root->left;
                delete root;
                return temp;
            }
            node* temp = findmin(root->right);
            root->data = temp->data;
            root->right = deletenode(root->right, temp->data);
        }
        return root;
    }

    bool searchnode(node* root, int value) {
        if (root == NULL) return false;
        if (root->data == value) return true;
        else if (value < root->data) return searchnode(root->left, value);
        else return searchnode(root->right, value);
    }

    void inorder(node* root) {
        if (root != NULL) {
            inorder(root->left);
            cout << root->data << " ";
            inorder(root->right);
        }
    }

public:
    bst() {
        root = NULL;
    }

    void insert(int value) {
        root = insertnode(root, value);
    }

    void remove(int value) {
        root = deletenode(root, value);
    }

    bool search(int value) {
        return searchnode(root, value);
    }

    void inordertraversal() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    bst tree;

    tree.insert(3);
    cout<<"Value inserted"<<endl;
    tree.insert(4);
    cout<<"Value inserted"<<endl;
    tree.insert(1);
    cout<<"Value inserted"<<endl;
    tree.insert(2);
    cout<<"Value inserted"<<endl;
    tree.insert(6);
    cout<<"Value inserted"<<endl;
    if(tree.search(5)){
        cout<<"Value found"<<endl;
    }else{
        cout<<"Not found"<<endl;
    }
    
    if(tree.search(6)){
        cout<<"Value found"<<endl;
    }else{
        cout<<"Not found"<<endl;
    }
    
    tree.remove(6);
    cout<<"Value removed"<<endl;
    cout<<"Inorder triversal: ";
    tree.inordertraversal();
}
