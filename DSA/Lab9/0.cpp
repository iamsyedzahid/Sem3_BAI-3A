Node* buildAVL(int arr[], int start, int end) {
    if (start > end)
        return NULL;

    int mid = (start + end) / 2;
    Node* root = new Node(arr[mid]);

    root->left  = buildAVL(arr, start, mid - 1);
    root->right = buildAVL(arr, mid + 1, end);

    root->height = 1 + max(height(root->left), height(root->right));

    return root;
}

void inorder(Node* r, int arr[], int &idx) {
    if (r == NULL) return;

    inorder(r->left, arr, idx);
    arr[idx++] = r->key;
    inorder(r->right, arr, idx);
}

Node* convertBSTtoAVL(Node* bstRoot) {
    if (bstRoot == NULL)
        return NULL;

    int arr[100];
    int idx = 0;

    inorder(bstRoot, arr, idx);

    return buildAVL(arr, 0, idx - 1);
}
//Inorder hamay array dega, arr = [10, 20, 25, 30, 40, 50]
/* middle element root banjaye gi
left half, left subtree banjaye ga aur
right half, right subtree banjaye ga
Recursion ki waja se balancing sahi hogi
nodes har recursive call se aise link hongay:
root->left  = buildAVL(left half)
root->right = buildAVL(right half)

for right rotation
y -> imbalanced node
x -> left child of y
t2 -> the right subtree of x
and in left rotation x is y and y is x and t2 is left subtree of y

the rotations were Left-Left and Left-Right
In right rotation, x becomes the new root, so the function will return x
In left rotation, y becomes the new root, so the function will return y
*/
