#include <iostream>

using namespace std;

int getMax(int arr[], int n) {
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

void countingSort(int arr[], int n, int exp, bool ascending) {
    int* output = new int[n];
    int count[10] = {0};

    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    if (ascending) {
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
    } else {
        for (int i = 8; i >= 0; i--) {
            count[i] += count[i + 1];
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        int position = count[digit] - 1;
        output[position] = arr[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    
    delete[] output;
}

void radixSort(int arr[], int n, bool ascending = true) {
    if (n == 0) return;

    int maxVal = getMax(arr, n);

    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSort(arr, n, exp, ascending);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int* arrDesc = new int[n];
    for (int i = 0; i < n; i++) {
        arrDesc[i] = arr[i];
    }

    cout << "Original Array: ";
    printArray(arr, n);

    radixSort(arr, n, true);
    cout << "\nSorted (Ascending): ";
    printArray(arr, n);

    radixSort(arrDesc, n, false);
    cout << "Sorted (Descending): ";
    printArray(arrDesc, n);

    delete[] arrDesc;

    return 0;
}
