#include <iostream>
#include <vector>
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

void inorder(Node *root)
{
    if (root)
    {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

void inorderStore(Node *root, vector<int> &arr)
{
    if (!root)
        return;
    inorderStore(root->left, arr);
    arr.push_back(root->data);
    inorderStore(root->right, arr);
}

float findMedian(Node *root)
{
    vector<int> arr;
    inorderStore(root, arr);
    int n = arr.size();
    if (n == 0)
        return -1;
    if (n % 2 == 1)
        return arr[n / 2];
    else
        return (arr[n / 2 - 1] + arr[n / 2]) / 2.0;
}

int countRange(Node *root, int a, int b)
{
    if (!root)
        return 0;

    if (root->data >= a && root->data <= b)
        return 1 + countRange(root->left, a, b) + countRange(root->right, a, b);
    else if (root->data < a)
        return countRange(root->right, a, b);
    else
        return countRange(root->left, a, b);
}

int main()
{
    Node *root = nullptr;
    int n, val;

    cout << "Enter number of nodes: ";
    cin >> n;

    cout << "Enter " << n << " values:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> val;
        root = insert(root, val);
    }

    cout << "\nInorder traversal (sorted): ";
    inorder(root);
    cout << endl;

    // Find Median
    float median = findMedian(root);
    cout << "Median of BST: " << median << endl;

    // Count nodes in range
    int a, b;
    cout << "\nEnter range [a b]: ";
    cin >> a >> b;

    int count = countRange(root, a, b);
    cout << "Nodes in range [" << a << ", " << b << "] = " << count << endl;
}