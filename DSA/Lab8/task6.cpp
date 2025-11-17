#include <iostream>
using namespace std;

struct ProductNode
{
    int id;
    int quantity;
    ProductNode *left, *right;
    ProductNode(int i, int q)
    {
        id = i;
        quantity = q;
        left = right = nullptr;
    }
};

class InventoryBST
{
    ProductNode *root;

    ProductNode *insert(ProductNode *node, int id, int quantity)
    {
        if (!node)
            return new ProductNode(id, quantity);
        if (id < node->id)
            node->left = insert(node->left, id, quantity);
        else if (id > node->id)
            node->right = insert(node->right, id, quantity);
        return node;
    }

    ProductNode *search(ProductNode *node, int id)
    {
        if (!node || node->id == id)
            return node;
        if (id < node->id)
            return search(node->left, id);
        return search(node->right, id);
    }

    void findMaxQuantity(ProductNode *node, int &maxQ, int &maxID)
    {
        if (!node)
            return;
        if (node->quantity > maxQ)
        {
            maxQ = node->quantity;
            maxID = node->id;
        }
        findMaxQuantity(node->left, maxQ, maxID);
        findMaxQuantity(node->right, maxQ, maxID);
    }

public:
    InventoryBST() { root = nullptr; }

    void insertProduct(int id, int quantity)
    {
        root = insert(root, id, quantity);
    }

    void updateQuantity(int id, int quantity)
    {
        ProductNode *p = search(root, id);
        if (p)
            p->quantity = quantity;
        else
            cout << "Product not found!\n";
    }

    void searchProduct(int id)
    {
        ProductNode *p = search(root, id);
        if (p)
            cout << "Product ID: " << p->id << ", Quantity: " << p->quantity << endl;
        else
            cout << "Product not found.\n";
    }

    void getMaxQuantityProduct()
    {
        int maxQ = -1, maxID = -1;
        findMaxQuantity(root, maxQ, maxID);
        cout << "Highest Quantity → Product ID: " << maxID << ", Quantity: " << maxQ << endl;
    }
};

int main()
{
    InventoryBST inv;
    inv.insertProduct(100, 20);
    inv.insertProduct(50, 10);
    inv.insertProduct(150, 40);
    inv.insertProduct(200, 35);

    inv.searchProduct(150);
    inv.getMaxQuantityProduct();
}
