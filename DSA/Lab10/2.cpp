#include <iostream>
#include <algorithm>

using namespace std;

bool isMaxHeap(int arr[], int n) {
    for (int i = (n / 2) - 1; i >= 0; i--) {
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;

        if (leftChild < n && arr[i] < arr[leftChild]) {
            return false;
        }

        if (rightChild < n && arr[i] < arr[rightChild]) {
            return false;
        }
    }
    return true;
}

void MaxHeapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        MaxHeapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        MaxHeapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        MaxHeapify(arr, i, 0);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << (i == n - 1 ? "" : ", ");
    }
    cout << endl;
}

int main() {
    int arr1[] = {8, 7, 6, 5, 4};
    int n1 = 5;

    cout << "Heap Check and Sort" << endl;
    cout << "Initial Array: ";
    printArray(arr1, n1);

    if (isMaxHeap(arr1, n1)) {
        cout << "Result: The array represents a Binary (Max) Heap." << endl;
    } else {
        cout << "Result: The array does NOT represent a Binary Heap." << endl;
    }

    heapSort(arr1, n1);

    cout << "Array after Heap Sort (Ascending): ";
    printArray(arr1, n1);
    
    return 0;
}
