#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct PivotStrategy {
    static const int FIRST = 0;
    static const int RANDOM = 1;
    static const int MIDDLE = 2;
    static const int MEDIAN = 3;
};

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int getMedianPivotIndex(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid]) {
        swap(&arr[low], &arr[mid]);
    }
    if (arr[low] > arr[high]) {
        swap(&arr[low], &arr[high]);
    }
    if (arr[mid] > arr[high]) {
        swap(&arr[mid], &arr[high]);
    }
    return mid;
}

int partition(int arr[], int low, int high, long long& comparisons, int strategy) {
    int pivotIndex;
    switch (strategy) {
        case PivotStrategy::FIRST:
            pivotIndex = low;
            break;
        case PivotStrategy::RANDOM:
            pivotIndex = low + rand() % (high - low + 1);
            break;
        case PivotStrategy::MIDDLE:
            pivotIndex = low + (high - low) / 2;
            break;
        case PivotStrategy::MEDIAN:
            pivotIndex = getMedianPivotIndex(arr, low, high);
            break;
    }

    int pivotValue = arr[pivotIndex];
    swap(&arr[pivotIndex], &arr[high]);

    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        comparisons++;
        if (arr[j] < pivotValue) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high, long long& comparisons, int strategy) {
    if (low < high) {
        int pi = partition(arr, low, high, comparisons, strategy);
        quickSort(arr, low, pi - 1, comparisons, strategy);
        quickSort(arr, pi + 1, high, comparisons, strategy);
    }
}

void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

void runSortTest(int arr[], int n, int strategy, const string& strategyName) {
    long long comparisons = 0;
    
    int* tempArr = new int[n];
    copyArray(arr, tempArr, n);
    
    cout << "--- Testing Strategy: " << strategyName << " ---" << endl;

    quickSort(tempArr, 0, n - 1, comparisons, strategy);
    
    cout << "Comparisons: " << comparisons << endl << endl;
    
    delete[] tempArr;
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(NULL));
    const int n = 50;

    int randomArr[n];
    for (int i = 0; i < n; i++) {
        randomArr[i] = rand() % 1000;
    }
    
    int sortedArr[n];
    for (int i = 0; i < n; i++) {
        sortedArr[i] = i * 2;
    }
    
    int reverseSortedArr[n];
    for (int i = 0; i < n; i++) {
        reverseSortedArr[n - 1 - i] = i * 2;
    }
    
    cout << "Array: ";
    printArray(randomArr, n);
    cout << endl;
    runSortTest(randomArr, n, PivotStrategy::FIRST, "First Element");
    runSortTest(randomArr, n, PivotStrategy::MIDDLE, "Middle Element");
    runSortTest(randomArr, n, PivotStrategy::MEDIAN, "Median-of-Three");
    runSortTest(randomArr, n, PivotStrategy::RANDOM, "Random Element");
    
    cout << "Array: ";
    printArray(sortedArr, n);
    cout << endl;
    runSortTest(sortedArr, n, PivotStrategy::FIRST, "First Element");
    runSortTest(sortedArr, n, PivotStrategy::MIDDLE, "Middle Element");
    runSortTest(sortedArr, n, PivotStrategy::MEDIAN, "Median-of-Three");
    runSortTest(sortedArr, n, PivotStrategy::RANDOM, "Random Element");

    cout << "Array: ";
    printArray(reverseSortedArr, n);
    cout << endl;
    runSortTest(reverseSortedArr, n, PivotStrategy::FIRST, "First Element");
    runSortTest(reverseSortedArr, n, PivotStrategy::MIDDLE, "Middle Element");
    runSortTest(reverseSortedArr, n, PivotStrategy::MEDIAN, "Median-of-Three");
    runSortTest(reverseSortedArr, n, PivotStrategy::RANDOM, "Random Element");

    return 0;
}
