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

int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n-1;
    while(low <= high) {
        int mid = (low + high) / 2;
        if(arr[mid] == key) return mid;
        else if(arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int main() {
    int arr[] = {34, 7, 23, 32, 5, 62};
    int n = sizeof(arr)/sizeof(arr[0]);
    int key = 15;  // last two digits of roll number

    insertionSort(arr, n);

    // check if 15 exists, if not add it
    bool found = false;
    for(int i = 0; i < n; i++) {
        if(arr[i] == key) {
            found = true;
            break;
        }
    }
    if(!found) {
        int newArr[100];
        for(int i = 0; i < n; i++) newArr[i] = arr[i];
        newArr[n] = key;
        n++;
        insertionSort(newArr, n);
        for(int i = 0; i < n; i++) arr[i] = newArr[i];
    }

    cout << "Sorted Array: ";
    for(int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    int index = binarySearch(arr, n, key);
    if(index != -1)
        cout << "Element " << key << " found at index " << index;
    else
        cout << "Element not found";

    return 0;
}
