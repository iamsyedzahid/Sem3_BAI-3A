#include <iostream>

using namespace std;

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int getMax(int arr[], int n) {
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

void countingSort(int arr[], int n, int exp) {
    int* output = new int[n];
    int count[10] = {0};

    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
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

void radixSort(int arr[], int n) {
    if (n == 0) return;
    int maxVal = getMax(arr, n);
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSort(arr, n, exp);
    }
}

int main() {
    int arr1[10] = {170, 45, 75, 90, 802, 24, 2, 66, 500, 32};
    int arr2[10] = {99, 1, 350, 4, 28, 60, 77, 900, 11, 42};
    int n1 = 10;
    int n2 = 10;
    int n_combined = n1 + n2;

    int* combinedArr = new int[n_combined];

    for (int i = 0; i < n1; i++) {
        combinedArr[i] = arr1[i];
    }
    for (int i = 0; i < n2; i++) {
        combinedArr[n1 + i] = arr2[i];
    }

    cout << "Combined and sorted using Radix Sort:" << endl;
    radixSort(combinedArr, n_combined);
    printArray(combinedArr, n_combined);

    delete[] combinedArr;

    return 0;
}
