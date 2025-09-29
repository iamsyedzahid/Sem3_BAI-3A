#include <iostream>
using namespace std;

void insertionSort(int arr[], int n) {
    for(int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

int main() {
    int arr[9] = {20, 12, 15, 2, 10, 1, 13, 9, 5};
    int n = 9;

    insertionSort(arr, n);

    // put maximum at middle
    int maxVal = arr[n-1];
    for(int i = n-1; i > n/2; i--) {
        arr[i] = arr[i-1];
    }
    arr[n/2] = maxVal;

    cout << "Modified Sorted Array: ";
    for(int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}
