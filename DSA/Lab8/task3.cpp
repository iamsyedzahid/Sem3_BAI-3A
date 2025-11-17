#include <iostream>
#include <string>
using namespace std;

struct node {
    string name;
    int roll;
    int score;
    node* left;
    node* right;
};

class bst {
    node* root;

    node* insertnode(node* root, int roll, const string& name, int score) {
        if (root == nullptr)
            return new node{name, roll, score, nullptr, nullptr};

        if (name < root->name)
            root->left = insertnode(root->left, roll, name, score);
        else if (name > root->name)
            root->right = insertnode(root->right, roll, name, score);

        return root;
    }

    node* findmin(node* root) {
        while (root && root->left != nullptr)
            root = root->left;
        return root;
    }
    
    node* deleteLowScores(node* root) {
        if (root == nullptr)
            return nullptr;

        root->left = deleteLowScores(root->left);
        root->right = deleteLowScores(root->right);

        if (root->score < 10) {
            
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                return nullptr;
            }
            
            else if (root->left == nullptr) {
                node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                node* temp = root->left;
                delete root;
                return temp;
            }
            else {
                node* temp = findmin(root->right);
                root->name = temp->name;
                root->roll = temp->roll;
                root->score = temp->score;
                root->right = deleteLowScores(root->right);
            }
        }
        return root;
    }

    bool searchnode(node* root, const string& name) {
        if (root == nullptr)
            return false;
        if (root->name == name)
            return true;
        else if (name < root->name)
            return searchnode(root->left, name);
        else
            return searchnode(root->right, name);
    }

    void inorder(node* root) {
        if (root != nullptr) {
            inorder(root->left);
            cout << root->name << " (" << root->roll << ", " << root->score << ")\n";
            inorder(root->right);
        }
    }

public:
    bst() : root(nullptr) {}

    void insert(int roll, const string& name, int score) {
        root = insertnode(root, roll, name, score);
    }

    void deleteLowScoreNodes() {
        root = deleteLowScores(root);
    }

    bool search(const string& name) {
        return searchnode(root, name);
    }

    void inordertraversal() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    bst tree;

    tree.insert(1, "zahid", 85);
    tree.insert(2, "saad", 90);
    tree.insert(3, "ahad", 70);
    tree.insert(4, "hamza", 5);
    tree.insert(5, "ibrahim", 95);
    tree.insert(6, "basil", 9);

    cout << "Inorder traversal before deletion:\n";
    tree.inordertraversal();

    tree.deleteLowScoreNodes();

    cout << "Inorder traversal after deleting scores < 10:\n";
    tree.inordertraversal();

    return 0;
}
