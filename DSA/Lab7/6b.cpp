#include <iostream>

using namespace std;

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
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

    cout << "Combined and sorted using Merge Sort:" << endl;
    mergeSort(combinedArr, 0, n_combined - 1);
    printArray(combinedArr, n_combined);

    delete[] combinedArr;

    return 0;
}
