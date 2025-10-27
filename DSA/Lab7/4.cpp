#include <iostream>
#include <string>

using namespace std;

class Product {
public:
    string name;
    int price;
    string description;
    bool availability;

    Product() : name(""), price(0), description(""), availability(false) {}

    Product(string n, int p, string d, bool a)
        : name(n), price(p), description(d), availability(a) {}
};

void swap(Product* a, Product* b) {
    Product temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Product arr[], int low, int high) {
    int pivotPrice = arr[high].price;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].price < pivotPrice) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(Product arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(Product arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << "Name: " << arr[i].name << ", Price: " << arr[i].price << endl;
    }
}

int main() {
    const int numProducts = 3;

    Product product1 = Product("Laptop", 1200, "High-performance laptop", true);
    Product product2 = Product("Mouse", 45, "Ergonomic wireless mouse", true);
    Product product3 = Product("Keyboard", 80, "Mechanical gaming keyboard", false);
    
    Product products[numProducts] = {product1, product2, product3};
    
    cout << "Original Product List:" << endl;
    printArray(products, numProducts);

    quickSort(products, 0, numProducts - 1);

    cout << "\nSorted Product List (by Price):" << endl;
    printArray(products, numProducts);

    return 0;
}
