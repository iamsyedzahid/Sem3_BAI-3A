bool isBSTUtil(Node *root, Node *&prev)
{
    if (root)
    {
        if (!isBSTUtil(root->left, prev))
            return false;

        if (prev != nullptr && root->data <= prev->data)
            return false;

        prev = root;
        return isBSTUtil(root->right, prev);
    }
    return true;
}

bool isBST(Node *root)
{
    Node *prev = nullptr;
    return isBSTUtil(root, prev);
}