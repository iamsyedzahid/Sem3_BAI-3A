int findKthLargest(int arr[], int n, int k) {
    if (k <= 0 || k > n) {
        cout << "Error: Invalid K value." << endl;
        return -1; // Indicate error
    }

    for (int i = n / 2 - 1; i >= 0; i--) {
        MaxHeapify(arr, n, i);
    }

    int heapSize = n;
    for (int i = 0; i < k - 1; i++) {
        swap(arr[0], arr[heapSize - 1]);
        heapSize--;
        MaxHeapify(arr, heapSize, 0);
    }
    return arr[0];
}
