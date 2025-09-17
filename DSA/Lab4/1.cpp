#include <iostream>
using namespace std;

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

int main() {
    const int SIZE = 10;
    int arr[SIZE];
    cout << "Enter 10 elements: ";
    for (int i = 0; i < SIZE; i++) {
        cin >> arr[i];
    }
    selectionSort(arr, SIZE);
    cout << "The 4 minimum elements are: ";
    for (int i = 0; i < 4; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}
