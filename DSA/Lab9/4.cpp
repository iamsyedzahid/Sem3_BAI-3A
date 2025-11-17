struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    int size;
};

Node* findKthSmallest(Node* root, int k) {
    if (root == NULL || k <= 0 || k > size(root))
        return NULL;

    int leftSize = size(root->left);
    
    if (leftSize + 1 == k)
        return root;

    if (k <= leftSize)
        return findKthSmallest(root->left, k);

    return findKthSmallest(root->right, k - leftSize - 1);
}

Node* findKthLargest(Node* root, int k) {
    if (root == NULL)
        return NULL;

    int N = size(root);
    if (k <= 0 || k > N)
        return NULL;

    int k_smallest = N - k + 1; 

    return findKthSmallest(root, k_smallest);
}
