#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *left, *right;
    Node(int val)
    {
        data = val;
        left = right = nullptr;
    }
};

Node *insert(Node *root, int val)
{
    if (root == nullptr)
        return new Node(val);

    if (val < root->data)
        root->left = insert(root->left, val);
    else if (val > root->data)
        root->right = insert(root->right, val);

    return root;
}

bool search(Node *root, int key)
{
    if (!root)
        return false;
    if (root->data == key)
        return true;
    if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

void inorder(Node *root)
{
    if (root)
    {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

int main()
{
    Node *root = nullptr;
    root = insert(root, 10);
    insert(root, 5);
    insert(root, 20);
    insert(root, 15);

    int val;
    cout << "Enter value to search: ";
    cin >> val;

    if (search(root, val))
        cout << "Value already exists!\n";
    else
    {
        cout << "Value not found. Inserting...\n";
        insert(root, val);
    }

    cout << "Inorder traversal: ";
    inorder(root);
}